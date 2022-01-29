#include "goal.h"

void Goal_Init(Goal *self, double x, double y1, double y2, GoalDirection direction)
{
    self->x = x;
    self->y1 = y1;
    self->y2 = y2;
    self->direction = direction;
}

static int Goal_is_direction_left(Goal *self)
{
    return self->direction == LeftGoal;
}

static int Goal_is_direction_right(Goal *self)
{
    return self->direction == RightGoal;
}

int Goal_IsBallInside(Goal *self, Ball *ball)
{
    if (ball->y - ball->radius < self->y1 || ball->y + ball->radius > self->y2)
    {
        return 0;
    }

    if (Goal_is_direction_left(self))
    {
        return (ball->x - ball->radius < self->x);
    }

    if (Goal_is_direction_right(self))
    {
        return (ball->x + ball->radius > self->x);
    }

    return 0;
}
