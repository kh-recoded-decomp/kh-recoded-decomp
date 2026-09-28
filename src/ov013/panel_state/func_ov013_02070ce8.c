#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x2ef];
    s8 startValue;
} PanelState;

typedef struct GridEntry {
    u8 pad_00[0x94];
    s32 flags;
} GridEntry;

extern PanelState *g_panelState_02074ce0;
extern int func_ov027_020b90a4(void *panel, int value);
extern void func_ov027_020b9580(void *panel, int value, int flag);
extern void func_ov027_020b96a0(void *panel, int value, u16 flag);

void func_ov013_02070ce8(void) {
    s32 count = 0;
    s8 startValue = g_panelState_02074ce0->startValue;
    s32 index = 0;
    s32 offset = startValue;
    if (startValue != 0) {
        offset = startValue - 1;
    } else {
        index = 1;
    }
    if (index >= 9) {
        return;
    }
    do {
        u8 *state = (u8 *)g_panelState_02074ce0;
        GridEntry **table = (GridEntry **)(state + 0xd150);
        GridEntry *entry = table[index];
        if ((u32)(entry->flags << 30) >> 31) {
            s32 entryOffset = offset + count;
            u8 *flagByte = state + entryOffset + 0x258;
            if (*flagByte != 0) {
                s32 panelId = index + 200;
                s32 result = func_ov027_020b90a4((u8 *)g_panelState_02074ce0 + 0x6818, panelId);
                func_ov027_020b9580((u8 *)g_panelState_02074ce0 + 0x6818, result, 1);
                u8 *state2 = (u8 *)g_panelState_02074ce0;
                result = func_ov027_020b90a4(state2 + 0x6818, panelId);
                u8 value = state2[entryOffset + 0x258];
                func_ov027_020b96a0((u8 *)g_panelState_02074ce0 + 0x6818, result, value - 1);
            }
            count = count + 1;
        }
        index = index + 1;
    } while (index < 9);
}
