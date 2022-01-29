#include <stdio.h>
#include <math.h>
#include "ball.h"

void Ball_Init(Ball *self, double x, double y, double vx, double vy, double ball_size)
{
    self->spawn_x = x;
    self->spawn_y = y;
    self->x = x;
    self->y = y;
    self->vx = vx;
    self->vy = vy;
    self->radius = ball_size;
    self->bounce = 0;
}

void Ball_Reset(Ball *self)
{
    self->x = self->spawn_x;
    self->y = self->spawn_y;
    self->vx = 0;
    self->vy = 0;
    self->bounce = 0;
}

void Ball_DetectAndBounceFromBallBoundary(Ball *self, double up, double down)
{
    if (self->y < up + self->radius)
    {
        self->vy = abs(self->vy);
    }
    else if (self->y > down - self->radius)
    {
        self->vy = -abs(self->vy);
    }
}

int Ball_DetectAndBounceFromPad1(Ball *self, double pad_x, double pad_y1, double pad_y2)
{
    if (self->y < pad_y1 - self->radius || self->y > pad_y2 + self->radius)
        return 0;
    if (self->x > pad_x + self->radius)
        return 0;

    self->x = pad_x + self->radius;
    self->vx = abs(self->vx);
    return 1;
}

int Ball_DetectAndBounceFromPad2(Ball *self, double pad_x, double pad_y1, double pad_y2)
{
    if (self->y < pad_y1 - self->radius || self->y > pad_y2 + self->radius)
        return 0;
    if (self->x < pad_x - self->radius)
        return 0;

    self->x = pad_x - self->radius;
    self->vx = -abs(self->vx);
    return 1;
}

void Ball_Move(Ball *self, double delta_time, double ball_speed)
{
    self->x += self->vx * delta_time * ball_speed;
    self->y += self->vy * delta_time * ball_speed;
}
