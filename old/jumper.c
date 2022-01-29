#include "jumper.h"
#include <math.h>

// Action
void Jumper_Jump(Jumper *self)
{
    // force = -2*dist/time²
    double force = self->jump_heigth * -2 / (self->jump_time * self->jump_time);
    self->acc_y += force;
}

void Jumper_SetDirection(Jumper *self, int direction)
{
    if (self->x < MAP_BOUNDARY_LEFT)
    {
        self->acc_x = self->move_force;
    }
    else if (self->x > MAP_BOUNDARY_RIGTH)
    {
        self->acc_x = -self->move_force;
    }
    else
    {
        // direction is either 0 or 1 or -1
        self->acc_x = direction * self->move_force;
    }
}


void Jumper_UpdateMouvements(Jumper *self, double dt)
{
    if (self->x < MAP_BOUNDARY_LEFT)
    {
        self->vel_x = fabs(self->vel_x);
    }
    else if (self->x > MAP_BOUNDARY_RIGTH)
    {
        self->vel_x = -fabs(self->vel_x);
    }

    // clamp speed to -1,1
    self->vel_x = self->vel_x > 1 ? 1 : self->vel_x;
    self->vel_x = self->vel_x < -1 ? -1 : self->vel_x;
    self->vel_y = self->vel_y > 1 ? 1 : self->vel_y;
    self->vel_y = self->vel_y < -1 ? -1 : self->vel_y;

    self->vel_x += self->acc_x;
    self->vel_y += self->acc_y;

    self->x += self->vel_x;
    self->y += self->vel_y;
}

// UpdateFlags
int Jumper_UpdateIsGrounded(Jumper *self, double ground_x1, double ground_x2, double ground_y)
{
    self->is_grounded = self->y - 0.01 < ground_y && self->x > ground_x1 && self->x > ground_x2;
}

int Jumper_UpdateIsAbleToJump(Jumper *self, double dt)
{
    self->jump_timer -= dt;
    if (self->jump_timer < 0)
    {
        self->jump_timer = self->jump_delay;
        self->is_able_to_jump = self->jump_timer < 0;
    }
}

// GetFlags
int Jumper_IsGrounded(Jumper *self) { return self->is_grounded; }
int Jumper_IsAbleToJump(Jumper *self) { return self->is_able_to_jump; }
