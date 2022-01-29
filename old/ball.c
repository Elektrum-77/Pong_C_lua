#include "ball.h"

void Ball_UpdatePhysics(Ball *self, double delta_time)
{

    if (self->x < GameContext_GetMapBoundaryLeft(self->GameContext) + self->radius)
    {
        self->vx = abs(self->vx);
        self->bounce++;
    }
    else if (self->x > GameContext_GetMapBoundaryRight(self->GameContext) - self->radius)
    {
        self->vx = -abs(self->vx);
        self->bounce++;
    }
    if (self->y < GameContext_GetMapBoundaryUp(self->GameContext) + self->radius)
    {
        self->vy = abs(self->vy);
        self->bounce++;
    }
    else if (self->y > GameContext_GetMapBoundaryDown(self->GameContext) - self->radius)
    {
        self->vy = -abs(self->vy);
        self->bounce++;
    }

    double speed = self->bounce;
    speed = (speed > 5) ? 5 : speed;
    self->x += self->vx * delta_time * speed;
    self->y += self->vy * delta_time * speed;
}