#include "nitro/types.h"

#pragma explicit_zero_data on

/* The busy wait starts in CPU-mode polling mode. */
int PMi_WaitBusyMethod = 2;

/* Initial power-management control value. */
u32 data_02055c48 = 0x00010000;
