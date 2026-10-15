#include "nitro/types.h"
#include "src/overlays/ov101/ListPortraitLayout.h"

typedef struct {
    u8 pad_00[0x10];
    s32 x;
    s32 y;
    u8 pad_18[0x18];
} StateBuffer;

typedef struct {
    s32 selectedItem;
    u8 pad_0004[0xCE04 - 0x4];
    StateBuffer buffers[2];
    s32 bufferCount;
    s32 pages[40];
} Ov101State;

extern void SetScreenOrthoCamera(void);
extern BOOL IsStateFlagSet(int setIndex, int bitIndex);
extern void func_ov001_0206ad28(void *list);

void UpdatePageBufferPositions(Ov101State *state)
{
    int item = state->selectedItem;
    int i;
    ListPortraitLayout *layout;
    ListPortraitEntry *position;
    StateBuffer *buffer;

    SetScreenOrthoCamera();
    if (!IsStateFlagSet(0, item) || state->bufferCount <= 0) {
        return;
    }
    layout = &gListPortraitLayouts[item];
    for (i = 0; i < state->bufferCount; i++) {
        buffer = &state->buffers[i];
        position = &layout->entries[state->pages[item]];
        buffer->x = position->x << 12;
        buffer->y = position->y << 12;
        func_ov001_0206ad28(buffer);
    }
}

