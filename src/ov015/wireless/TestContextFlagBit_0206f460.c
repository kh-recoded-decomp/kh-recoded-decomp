#include "nitro/types.h"

typedef struct {
    u32 words[3];
} FlagBitsBlock;

extern const FlagBitsBlock g_contextFlagBits_02079f4c;
extern u8 *g_context_0207e960;

BOOL TestContextFlagBit_0206f460(int index)
{
    FlagBitsBlock localBits = g_contextFlagBits_02079f4c;
    return (g_context_0207e960[0xba] & localBits.words[index]) != 0;
}
