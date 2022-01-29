#ifndef GOAL_H_
#define GOAL_H_

#include "../ball/ball.h"

typedef enum
{
    LeftGoal,
    RightGoal
} GoalDirection;

typedef struct goal
{
    double x, y1, y2;
    GoalDirection direction;
} Goal;

void Goal_Init(Goal *self, double x, double y1, double y2, GoalDirection direction);
int Goal_IsBallInside(Goal *self, Ball *ball);

int Goal_GetGoalCount(Goal *self);

#endif
