#include "nitro/types.h"

typedef struct BufferItem {
    u8 data[0x30];
} BufferItem;

typedef struct BufferList {
    BufferItem *items;
    s8 count;
} BufferList;

typedef struct ChannelSlot {
    BufferList buffers;
    u8 pad_08[0x20];
} ChannelSlot;

typedef struct ChannelManager {
    u32 flags;
    BufferList primaryBuffers;
    u8 pad_0c[0x20];
    ChannelSlot slots[3];
} ChannelManager;

extern void FreeBufferList(BufferList *list);
extern void RemoveTaggedListEntries(u32 callback);
extern void RefreshMenuWindows(void);

void ReleaseChannelManagerResources(ChannelManager *manager)
{
    int i;

    FreeBufferList(&manager->primaryBuffers);
    i = 0;
    do {
        FreeBufferList((BufferList *)((u32)manager + 0x2c + i * sizeof(ChannelSlot)));
        i = i + 1;
    } while (i < 3);
    RemoveTaggedListEntries((u32)RefreshMenuWindows);
}
