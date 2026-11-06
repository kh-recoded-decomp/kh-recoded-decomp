#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyPxiChannelState(void);
extern void InitTextWindowControllerTask(void);

void *gTextWindowControllerTaskClass[5] = {
    (void *)0x000E001B,
    (void *)InitTextWindowControllerTask,
    (void *)DestroyPxiChannelState,
    (void *)0x00000020,
    NULL,
};
