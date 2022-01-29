#ifndef JUMPER_H_
#define JUMPER_H_

#include "map.h"

typedef struct jumper
{
    // PYHISCS
    double x;
    double y;
    double acc_x;
    double acc_y;
    double vel_x;
    double vel_y;
    double size_x;
    double size_y;

    //Flags
    int is_grounded;
    int is_able_to_jump;

    // Timers
    double jump_timer;
    
    // DATA
    double jump_delay;
    double jump_heigth;
    double jump_time; // always 1 ?
    double move_force;
    double move_speed;

} Jumper;

// Action
void Jumper_Jump(Jumper* self);
void Jumper_SetDirection(Jumper* self, int direction);

// void Jumper_Update(Jumper* self, double dt);
// void Jumper_UpdateTimers(Jumper* self, double dt);
void Jumper_UpdateMovements(Jumper* self, double dt);

// UpdateFlags
int Jumper_UpdateIsGrounded(Jumper* self, double ground_x1, double ground_x2, double ground_y);
int Jumper_UpdateIsAbleToJump(Jumper* self, double dt);

// GetFlags
int Jumper_IsGrounded(Jumper* self);
int Jumper_IsAbleToJump(Jumper* self);



#endif