#include "nitro/types.h"

typedef struct ActorSlotHeader {
    u8 pad_00[0x6];
    s16 height;
    u8 pad_08[0xc];
    s32 posY;
    u8 pad_18[0x8];
    u32 drawParam;
    u8 pad_24[0x2];
    u16 drawFlags;
    u8 pad_28[0x2];
    u8 priority : 5;
    u8 priorityPad : 3;
    u8 pad_2B[0x5];
} ActorSlotHeader;

typedef struct ActorSlot {
    ActorSlotHeader header;
    u8 pad_30[0x44];
    void *resource;
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0xe7c];
    void *pendingResource;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

typedef void (*TextureLoader)(const u8 *src, u32 destSlotAddr, u32 size);

extern ActorSlotContext data_ov036_020c3920;
extern TextureLoader data_02060570;
extern void LoadTextureInChunks_020bc8b4(const u8 *src, u32 destSlotAddr, u32 size);
extern void *func_0202c940(void *resource, void *arg, int mode);
extern void func_0202c690(int mode);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void SetSlotKeyAndRebind_0206a94c(ActorSlot *slot, void *key, int flags);
extern void ReleaseResourceSlot_0202ca18(void *resource);
extern void ReleaseSharedRecordSlot_0202c8a8(void *resource);
extern int func_ov036_020bb8cc(int height);

void SwapActorSlotResource_020bc978(ActorSlot *slot)
{
    void *oldResource = slot->resource;
    void *key;
    ActorSlotHeader saved;

    slot->resource = data_ov036_020c3920.work->pendingResource;
    data_ov036_020c3920.work->pendingResource = NULL;
    data_02060570 = LoadTextureInChunks_020bc8b4;
    key = func_0202c940(slot->resource, NULL, 1);
    func_0202c690(1);
    func_01ff89a8(slot, &saved, sizeof(ActorSlotHeader));
    SetSlotKeyAndRebind_0206a94c(slot, key, 0);
    slot->header.drawFlags = saved.drawFlags;
    slot->header.drawParam = saved.drawParam;
    if (saved.priority != 0) {
        slot->header.priority = saved.priority;
    }
    if (oldResource != NULL) {
        ReleaseResourceSlot_0202ca18(oldResource);
        ReleaseSharedRecordSlot_0202c8a8(oldResource);
    } else if (slot->header.posY == 0) {
        slot->header.posY = func_ov036_020bb8cc(slot->header.height);
    }
}
