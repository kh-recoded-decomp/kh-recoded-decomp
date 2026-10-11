#ifndef RECODED_SESSION_FLAGS_H
#define RECODED_SESSION_FLAGS_H

#include "nitro/types.h"

void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
void SetSessionFlag(int bitOffset);

#endif
