#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitTextWindowTask(void);
extern void DestroyTextWindowTask(void);

void *gTextWindowTaskClass[5] = {
    (void *)0x000E001B,
    (void *)InitTextWindowTask,
    (void *)DestroyTextWindowTask,
    (void *)0x000068B4,
    NULL,
};
