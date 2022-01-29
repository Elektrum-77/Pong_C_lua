#ifndef PLATFORM_H_
#define PLATFORM_H_

typedef struct platform
{
    double x;
    double x_size;
    double y;
} Platform;

double Platform_GetPositionStartX(Platform* self);
double Platform_GetPositionEndX(Platform* self);
double Platform_GetPositionY(Platform* self);

#endif