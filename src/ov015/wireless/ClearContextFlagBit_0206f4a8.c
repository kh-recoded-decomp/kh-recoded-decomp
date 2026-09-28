#include "nitro/types.h"

typedef struct {
    u32 words[3];
} FlagBitsBlock;

extern const FlagBitsBlock g_contextFlagBits_02079f94;
extern u8 *g_context_0207e960;

void ClearContextFlagBit_0206f4a8(int index)
{
    FlagBitsBlock localBits = g_contextFlagBits_02079f94;
    g_context_0207e960[0xba] &= (u8)~localBits.words[index];
}
