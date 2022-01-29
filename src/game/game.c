#include "game.h"

void Game_Init(Game *self, Goal *goal1, Goal *goal2, Score *score1, Score *score2, Pad *player1, Pad *player2, Ball *ball, GameConfig *config, GameBorder *border, double pad_speed, double ball_speed, double border_left, double border_right, double border_up, double border_down)
{
    self->goal1 = goal1;
    self->goal2 = goal2;
    self->score1 = score1;
    self->score2 = score2;
    self->player1 = player1;
    self->player2 = player2;
    self->ball = ball;

    self->config = config;
    self->border = border;

    self->pad_speed = pad_speed;
    self->ball_speed = ball_speed;

    self->border_left = border_left;
    self->border_right = border_right;
    self->border_up = border_up;
    self->border_down = border_down;
}

void Game_UpdatePad(Game *self, Pad *pad, double delta_time)
{
    Pad_DetectAndCollideWithPadBoundary(pad, self->border_up, self->border_down);
    Pad_Move(pad, delta_time, self->pad_speed);
}

void Game_UpdateBall(Game *self, double delta_time)
{
    Ball_DetectAndBounceFromPad1(self->ball, self->player1->x, self->player1->y, self->player1->y2);
    Ball_DetectAndBounceFromPad2(self->ball, self->player2->x, self->player2->y, self->player2->y2);
    Ball_DetectAndBounceFromBallBoundary(self->ball, self->border_up, self->border_down);
}

void Game_CheckGoal(Game *self, Goal *goal, Score *enemy_score)
{
    if (Goal_IsBallInside(goal, self->ball))
    {
        Score_Increment(enemy_score);
        Ball_Reset(self->ball);
    }
}

void Game_Update(Game *self, double delta_time)
{
    Game_UpdatePad(self, self->player1, delta_time);
    Game_UpdatePad(self, self->player2, delta_time);
    Game_UpdateBall(self, delta_time);

    Game_CheckGoal(self, self->goal1, self->score2);
    Game_CheckGoal(self, self->goal2, self->score1);

    Ball_Move(self->ball, delta_time, self->ball_speed);
}
