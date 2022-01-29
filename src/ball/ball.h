#ifndef BALL_H_
#define BALL_H_

typedef struct ball
{
    void (*IncPlayer1Score)(void);
    void (*IncPlayer2Score)(void);
    double spawn_x, spawn_y;
    double x, y, vx, vy;
    double radius;
    double bounce;
} Ball;

void Ball_Init(Ball *self, double x, double y, double vx, double vy, double ball_size);
void Ball_DetectAndBounceFromBallBoundary(Ball *self, double up, double down);
int Ball_DetectAndBounceFromPad1(Ball *self, double pad_x, double pad_y1, double pad_y2);
int Ball_DetectAndBounceFromPad2(Ball *self, double pad_x, double pad_y1, double pad_y2);
void Ball_Move(Ball *self, double delta_time, double ball_speed);
void Ball_Reset(Ball *self);

#endif