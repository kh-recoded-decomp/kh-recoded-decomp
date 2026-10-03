#include "nitro/types.h"

typedef struct MenuScreenEntry {
    u8 pad_00[0x8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s32 param;
    u32 fileIndex;
} MenuScreenEntry;

typedef struct MenuScreenState {
    u8 pad_00[0x4];
    s32 screenId;
    u8 pad_08[0x4];
    s32 archiveBase;
    u8 pad_10[0x7fa8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s32 param;
} MenuScreenState;

extern MenuScreenState *data_ov023_020b6f64;

extern void *func_ov027_020ba1d8(void *resource);
extern MenuScreenEntry *FindChainEntryById_020b5b6c(void *node, u16 id);
extern void *QueueFileLoadRequest_020ba114(u32 archiveId, int loadMode, void (*callback)(void *), void *userData);
extern void LoadMenuScreenResource_020b5b94(void *resource);
extern void func_ov001_0207b6f4(void);
extern void func_ov001_0207b4d8(void);
extern void func_ov027_020ba1e0(void *resource, int release);

void ApplyMenuScreenEntry_020b5bcc(void *resource)
{
    MenuScreenState *state = data_ov023_020b6f64;
    MenuScreenEntry *entry = FindChainEntryById_020b5b6c(func_ov027_020ba1d8(resource), state->screenId);

    if (entry != NULL) {
        state->x = entry->x;
        state->y = entry->y;
        state->width = entry->width << 3;
        state->height = entry->height << 3;
        state->param = entry->param;
        QueueFileLoadRequest_020ba114(((state->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (entry->fileIndex & 0x1ff),
                                      1, LoadMenuScreenResource_020b5b94, NULL);
    } else {
        state->width = 0;
        state->height = 0;
        state->param = 0;
        func_ov001_0207b6f4();
        func_ov001_0207b4d8();
    }
    func_ov027_020ba1e0(resource, 1);
}
