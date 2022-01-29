#ifndef GAME_H_
#define GAME_H_

#include "../pad/pad.h"
#include "../ball/ball.h"
#include "../goal/goal.h"
#include "../score/score.h"

typedef struct game_config
{
    double ball_speed, pad_speed;
} GameConfig;

typedef struct game_border
{
    double left, right, up, down;
} GameBorder;


typedef struct game
{
    Goal *goal1;
    Goal *goal2;
    Score *score1;
    Score *score2;
    Pad *player1;
    Pad *player2;
    Ball *ball;

    GameConfig *config;
    GameBorder *border;

    double ball_speed;
    double pad_speed;

    double border_left, border_right, border_up, border_down;

} Game;

void Game_Init(Game *self, Goal *goal1, Goal *goal2, Score *score1, Score *score2, Pad *player1, Pad *player2, Ball *ball, GameConfig *config, GameBorder *border, double pad_speed, double ball_speed, double border_left, double border_right, double border_up, double border_down);
void Game_Update(Game *self, double delta_time);

#endif