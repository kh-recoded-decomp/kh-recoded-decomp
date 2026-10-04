#include "nitro/types.h"

extern int GetPlayerEntryCount_02050050(int player, u32 id);
extern void *func_ov027_020ba2a8(void *container, int index);
extern void func_ov087_020c4860(void *scene, const u16 *text);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void ShowPromptAndStoreEntryCount_020c49fc(u8 *scene)
{
    int count = GetPlayerEntryCount_02050050(0, 9);

    func_ov087_020c4860(scene, func_ov027_020ba2a8(scene + 0xb64, 0x18));
    WriteSessionPackedBits_0206459c(0x1a0f, 3, count);
}

