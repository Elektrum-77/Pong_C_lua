#ifndef SCORE_H_
#define SCORE_H_

typedef struct score
{
    int points;
} Score;

void Score_Init(Score *self);
void Score_Increment(Score *self);
int Score_Get(Score *self);

#endif