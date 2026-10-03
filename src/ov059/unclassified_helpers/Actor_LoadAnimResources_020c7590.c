#include "nitro/types.h"

typedef struct AnimSlot {
    u8 data[0x2c];
} AnimSlot;

typedef struct AnimHolder {
    u32 pad_00;
    u8 player[1];
} AnimHolder;

typedef struct Actor {
    u8 pad_0000[0x230];
    AnimHolder *anim;
    u8 pad_0234[0x76c - 0x234];
    AnimSlot animSlots[1];
    u8 pad_0798[0x908 - 0x798];
    int (*mapKindToSlot)(int kind);
    u8 pad_090c[0x930 - 0x90c];
    u8 playerIndex;
    u8 pad_0931[0x93c - 0x931];
    int state;
    u8 pad_0940[0x1828 - 0x940];
    u16 effectGroupId;
} Actor;

typedef struct NameList {
    const char *names[3];
} NameList;

typedef struct SlotList {
    int slots[3];
} SlotList;

typedef struct GroupDesc {
    const char *name;
    int count;
    int stride;
    BOOL fixed;
    int reserved;
} GroupDesc;

extern const NameList data_ov059_020cfef0;
extern const SlotList data_ov059_020cfdf0;
extern const char data_ov059_020cff0c[];
extern const char data_ov059_020cff18[];
extern const char *data_0205615c[];
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern char *STD_ConcatString_02010cc8(char *dst, const char *src);
extern void AcquireSharedRecordState_020a9054(AnimSlot *slot, const char *name, void *player, int context);
extern void ZeroBytes0x14_020a8adc(void *obj);
extern u16 func_ov021_020a89a8(GroupDesc *desc);
extern void LoadActorModel_020c7510(Actor *actor);
extern int MapKindToSlotIndex_020c7a24(int kind);

void Actor_LoadAnimResources_020c7590(Actor *actor) {
    char path[128];
    NameList names;
    SlotList slots;
    GroupDesc desc;
    int context = actor->playerIndex + 8;
    int i;

    names = data_ov059_020cfef0;
    slots = data_ov059_020cfdf0;
    for (i = 0; i < 3; i++) {
        OS_SPrintf_02002428(path, data_ov059_020cff0c, data_0205615c[actor->state]);
        STD_ConcatString_02010cc8(path, names.names[i]);
        AcquireSharedRecordState_020a9054(&actor->animSlots[slots.slots[i]], path, actor->anim->player, context);
    }
    ZeroBytes0x14_020a8adc(&desc);
    OS_SPrintf_02002428(path, data_ov059_020cff18);
    desc.count = 1;
    desc.stride = 1;
    desc.fixed = FALSE;
    desc.name = path;
    actor->effectGroupId = func_ov021_020a89a8(&desc);
    LoadActorModel_020c7510(actor);
    actor->mapKindToSlot = MapKindToSlotIndex_020c7a24;
}
