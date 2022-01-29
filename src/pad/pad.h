#ifndef PAD_H_
#define PAD_H_

typedef struct pad
{
    double x, y, y2;
    double vy;
    double length;
} Pad;

void Pad_Init(Pad *self, double x, double y, double length);
void Pad_SetDirection(Pad *self, double vy);
void Pad_DetectAndCollideWithPadBoundary(Pad *self, double up, double down);
void Pad_Move(Pad *self, double delta_time, double pad_speed);

#endif