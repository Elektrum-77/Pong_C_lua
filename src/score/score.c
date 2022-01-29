#include "score.h"

void Score_Init(Score *self)
{
    self->points = 0;
}

void Score_Increment(Score *self)
{
    self->points++;
}
int Score_Get(Score *self)
{
    return self->points;
}