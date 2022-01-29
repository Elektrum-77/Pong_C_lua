#include <stdlib.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lua.h>
#include <math.h>

static double MAP_WIDTH = 0;
static double MAP_HEIGHT = 0;

int SetMapSizeLua(lua_State *L)
{
    MAP_WIDTH = lua_tonumber(L, 1);
    MAP_HEIGHT = lua_tonumber(L, 2);
    return 0;
}

typedef struct ball
{
    double x;
    double y;
    double vx;
    double vy;
    double radius;
    int bounce;
} Ball;

Ball BALL = {
    .x = 100,
    .y = 100,
    .vx = 100,
    .vy = 100,
    .radius = 50,
    .bounce = 1,
};

int GetBallLua(lua_State *L)
{
    lua_newtable(L);
    lua_pushnumber(L, BALL.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, BALL.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, BALL.vx);
    lua_setfield(L, -2, "vx");
    lua_pushnumber(L, BALL.vy);
    lua_setfield(L, -2, "vy");
    lua_pushnumber(L, BALL.radius);
    lua_setfield(L, -2, "radius");
    return 1;
}

int UpdateBallLua(lua_State *L)
{
    double dt = lua_tonumber(L, 1);

    if (BALL.x < BALL.radius)
    {
        BALL.vx = abs(BALL.vx);
        BALL.bounce++;
    }
    else if (BALL.x > MAP_WIDTH - BALL.radius)
    {
        BALL.vx = -abs(BALL.vx);
        BALL.bounce++;
    }
    if (BALL.y < BALL.radius)
    {
        BALL.vy = abs(BALL.vy);
        BALL.bounce++;
    }
    else if (BALL.y > MAP_HEIGHT - BALL.radius)
    {
        BALL.vy = -abs(BALL.vy);
        BALL.bounce++;
    }

    double speed = BALL.bounce;
    speed = (speed > 5) ? 5 : speed;
    BALL.x += BALL.vx * dt * speed;
    BALL.y += BALL.vy * dt * speed;

    return 0;
}

static double SCORE = 0;
int UpdateScoreLua(lua_State *L)
{
    double dt = lua_tonumber(L, 1);
    double cursor_x = lua_tonumber(L, 2);
    double cursor_y = lua_tonumber(L, 3);

    double dist_x = BALL.x - cursor_x;
    double dist_y = BALL.y - cursor_y;
    double dist_sqr = dist_x*dist_x + dist_y*dist_y;
    
    SCORE += (BALL.radius * BALL.radius - dist_sqr)*0.01 * dt;

    return 0;
}

int GetScoreLua(lua_State *L)
{
    lua_pushnumber(L, SCORE);
    return 1;
}

static const struct luaL_reg AllFunctionLua[] = {

    // {"StartGame", StartGameLua},
    {"SetMapSize", SetMapSizeLua},
    {"GetBall", GetBallLua},
    {"UpdateBall", UpdateBallLua},
    {"UpdateScore", UpdateScoreLua},
    {"GetScore", GetScoreLua},
    // {"AdvanceTime", AdvanceTimeLua},
    // {"MovePlayer", MovePlayerLua},
    {NULL, NULL}, // sentinel
};

int luaopen_main_c(lua_State *L)
{
    lua_newtable(L);
    luaL_register(L, NULL, AllFunctionLua);

    return 1;
}
