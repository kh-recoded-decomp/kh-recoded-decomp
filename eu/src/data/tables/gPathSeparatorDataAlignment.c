#include "nitro/types.h"

#pragma define_section pathSeparatorAlignment ".data" RW

/* Retained zero alignment bytes, not additional string characters. */
__declspec(pathSeparatorAlignment) u8 gPathSeparatorDataAlignment[2] = {0, 0};
