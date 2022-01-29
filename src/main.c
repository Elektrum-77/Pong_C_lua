#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lua.h>
#include <math.h>

#include "ball/ball.h"
#include "pad/pad.h"
#include "goal/goal.h"
#include "score/score.h"
#include "game/game.h"

static GameConfig GAME_CONFIG;
static GameBorder GAME_BORDER;
static Game GAME;

static Score SCORE1;
static Score SCORE2;
static Goal GOAL1;
static Goal GOAL2;
static Pad PAD1;
static Pad PAD2;
static Ball BALL;

void IncPlayer1Score(void)
{
    Score_Increment(&SCORE1);
}
void IncPlayer2Score(void)
{
    Score_Increment(&SCORE2);
}

int InitGameLua(lua_State *L)
{

    GAME_BORDER.left = lua_tonumber(L, 1);
    GAME_BORDER.right = lua_tonumber(L, 2);
    GAME_BORDER.up = lua_tonumber(L, 3);
    GAME_BORDER.down = lua_tonumber(L, 4);

    double pad_length = lua_tonumber(L, 5);
    GAME_CONFIG.pad_speed = lua_tonumber(L, 6);
    double ball_size = lua_tonumber(L, 7);
    GAME_CONFIG.ball_speed = lua_tonumber(L, 8);

    double x = GAME_BORDER.left + abs(GAME_BORDER.right - GAME_BORDER.left) / 2;
    double y = GAME_BORDER.up + abs(GAME_BORDER.down - GAME_BORDER.up) / 2;

    Score_Init(&SCORE1);
    Score_Init(&SCORE2);

    Goal_Init(&GOAL1, GAME_BORDER.left, GAME_BORDER.up, GAME_BORDER.down, LeftGoal);
    Goal_Init(&GOAL2, GAME_BORDER.right, GAME_BORDER.up, GAME_BORDER.down, RightGoal);

    Pad_Init(&PAD1, GAME_BORDER.left, y - pad_length / 2, pad_length);
    Pad_Init(&PAD2, GAME_BORDER.right, y - pad_length / 2, pad_length);

    BALL.IncPlayer1Score = &IncPlayer1Score;
    BALL.IncPlayer2Score = &IncPlayer2Score;
    Ball_Init(&BALL, x, y, 0, 0, ball_size);

    Game_Init(&GAME, &GOAL1, &GOAL2, &SCORE1, &SCORE2, &PAD1, &PAD2, &BALL, &GAME_CONFIG, &GAME_BORDER, GAME_CONFIG.pad_speed, GAME_CONFIG.ball_speed, GAME_BORDER.left, GAME_BORDER.right, GAME_BORDER.up, GAME_BORDER.down);

    return 0;
}

int LaunchBallLua(lua_State *L)
{
    if (BALL.vx != 0)
        return 0;

    double vx = (rand() % 2) * 2 - 1;
    double vy = (rand() % 2) * 2 - 1;

    BALL.vx = vx;
    BALL.vy = vy;

    return 0;
}

int UpdateGameLua(lua_State *L)
{
    double delta_time = lua_tonumber(L, 1);

    Game_Update(&GAME, delta_time);

    return 0;
}

int GetBallLua(lua_State *L)
{
    lua_newtable(L);
    lua_pushnumber(L, BALL.x - BALL.radius);
    lua_setfield(L, -2, "x1");
    lua_pushnumber(L, BALL.y - BALL.radius);
    lua_setfield(L, -2, "y1");
    lua_pushnumber(L, BALL.radius * 2);
    lua_setfield(L, -2, "x2");
    lua_pushnumber(L, BALL.radius * 2);
    lua_setfield(L, -2, "y2");
    return 1;
}

int GetScore1Lua(lua_State *L)
{
    lua_pushinteger(L, Score_Get(&SCORE1));
    return 1;
}
int GetScore2Lua(lua_State *L)
{
    lua_pushinteger(L, Score_Get(&SCORE2));
    return 1;
}

int GetPad1Lua(lua_State *L)
{
    lua_newtable(L);
    lua_pushnumber(L, PAD1.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, PAD1.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, PAD1.y2);
    lua_setfield(L, -2, "y2");
    lua_pushnumber(L, PAD1.length);
    lua_setfield(L, -2, "length");
    return 1;
}

int GetPad2Lua(lua_State *L)
{
    lua_newtable(L);
    lua_pushnumber(L, PAD2.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, PAD2.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, PAD2.y2);
    lua_setfield(L, -2, "y2");
    lua_pushnumber(L, PAD2.length);
    lua_setfield(L, -2, "length");
    return 1;
}

int SetPad1DirectionLua(lua_State *L)
{
    double vy = lua_tonumber(L, 1);
    Pad_SetDirection(&PAD1, vy);
    return 0;
}

int SetPad2DirectionLua(lua_State *L)
{
    double vy = lua_tonumber(L, 1);
    Pad_SetDirection(&PAD2, vy);
    return 0;
}

static const struct luaL_reg AllFunctionLua[] = {

    {"InitGame", InitGameLua},
    {"UpdateGame", UpdateGameLua},
    {"LaunchBall", LaunchBallLua},

    {"GetBall", GetBallLua},
    {"GetScore1", GetScore1Lua},
    {"GetScore2", GetScore2Lua},
    {"GetPad1", GetPad1Lua},
    {"GetPad2", GetPad2Lua},
    {"SetPad1Direction", SetPad1DirectionLua},
    {"SetPad2Direction", SetPad2DirectionLua},

    {NULL, NULL}, // sentinel
};

int luaopen_main_c(lua_State *L)
{
    lua_newtable(L);
    luaL_register(L, NULL, AllFunctionLua);

    return 1;
}
