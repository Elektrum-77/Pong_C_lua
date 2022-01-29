#ifndef BALL_H_
#define BALL_H_

typedef void* GameContext;

double GameContext_GetMapBoundaryLeft(GameContext game_context);
double GameContext_GetMapBoundaryRight(GameContext game_context);
double GameContext_GetMapBoundaryUp(GameContext game_context);
double GameContext_GetMapBoundaryDown(GameContext game_context);

typedef struct ball
{
    double x;
    double y;
    double vx;
    double vy;
    double radius;
    int bounce;

    GameContext GameContext;
} Ball;



#endif