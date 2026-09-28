/* OS types, with the NitroSDK's names. */
#ifndef NITRO_OS_TYPES_H
#define NITRO_OS_TYPES_H

#include "nitro/types.h"

/* What OS_DisableInterrupts returns and OS_RestoreInterrupts takes: the CPSR's IRQ-disable bit
 * as it was. An enum in the SDK; built with `-enum int`, the same as int. */
typedef int OSIntrMode;

/* The 64-bit tick count (OS_GetTick). */
typedef u64 OSTick;

#endif
