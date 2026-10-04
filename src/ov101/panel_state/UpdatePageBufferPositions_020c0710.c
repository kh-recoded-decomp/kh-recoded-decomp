#include "nitro/types.h"

typedef struct {
    s32 id;
    s32 x;
    s32 y;
} PagePosition;

typedef struct {
    PagePosition pages[30];
    u8 pad_168[8];
} ItemLayout;

typedef struct {
    u8 pad_00[0x10];
    s32 x;
    s32 y;
    u8 pad_18[0x18];
} StateBuffer;

typedef struct {
    s32 selectedItem;
    u8 pad_0004[0xCDFC - 0x4];
    StateBuffer buffers[2];
    s32 bufferCount;
    s32 pages[40];
} Ov101State;

extern ItemLayout data_ov101_020c139c[];
extern void func_ov001_0206aa7c(void);
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);
extern void NNS_FndInitListWithOffset0_0206ad28(void *list);

void UpdatePageBufferPositions_020c0710(Ov101State *state)
{
    int item = state->selectedItem;
    int i;
    ItemLayout *layout;
    PagePosition *position;
    StateBuffer *buffer;

    func_ov001_0206aa7c();
    if (!IsStateFlagSet_020c07a8(0, item) || state->bufferCount <= 0) {
        return;
    }
    layout = &data_ov101_020c139c[item];
    for (i = 0; i < state->bufferCount; i++) {
        buffer = &state->buffers[i];
        position = &layout->pages[state->pages[item]];
        buffer->x = position->x << 12;
        buffer->y = position->y << 12;
        NNS_FndInitListWithOffset0_0206ad28(buffer);
    }
}
