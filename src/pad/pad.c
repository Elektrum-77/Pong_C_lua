
#include "pad.h"

void Pad_Init(Pad *self, double x, double y, double length)
{
    self->x = x;
    self->y = y;
    self->y2 = y+length;
    self->length = length;
}

void Pad_SetDirection(Pad *self, double vy)
{
    self->vy = vy;
}

void Pad_DetectAndCollideWithPadBoundary(Pad *self, double up, double down)
{
    if (self->y < up)
    {
        self->y = up;
        self->y2 = up + self->length;
    }

    if (self->y2 > down)
    {
        self->y = down - self->length;
        self->y2 = down;
    }
}

void Pad_Move(Pad *self, double delta_time, double pad_speed)
{
    double dy = self->vy * delta_time * pad_speed;
    self->y += dy;
    self->y2 += dy;
}