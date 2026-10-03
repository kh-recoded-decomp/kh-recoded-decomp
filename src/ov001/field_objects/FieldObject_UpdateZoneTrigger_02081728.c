#include "nitro/types.h"

typedef struct {
    u8 pad0[0x214];
    u32 lowBits : 6;
    u32 lockedBit : 1;
    u32 highBits : 25;
    u8 pad218[0x27f1 - 0x218];
    u8 bit0 : 1;
    u8 zoneIndex : 3;
    u8 restBits : 4;
    u8 pad27f2[6];
    s8 state;
} FieldGlobal;

typedef struct {
    u8 pad0[0x85];
    u8 zoneIndex;
} SceneOwner;

typedef struct {
    u8 pad0[8];
    SceneOwner *owner;
    u8 pad0c[0x38 - 0x0c];
    u8 slotIndex;
    u8 pad39[0x4e - 0x39];
    u16 drawFlags;
    u8 pad50[0x5a - 0x50];
    u8 flags;
} SceneObject;

typedef void (*EntryCallback)(u8 *entry, int arg);

extern FieldGlobal *data_ov001_020a0460;
extern u8 data_020608c8;

extern int func_ov001_02063838(void);
extern int func_ov001_020642a0(void);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, int set);
extern void *func_ov001_0206dc4c(int index);
extern BOOL SceneObject_IsPointWithinOneUnit_02081a88(SceneObject *obj, void *point);
extern int func_ov001_0207f810(SceneObject *obj);
extern void SpawnSoundSlot_0204da8c(int a, int b, int c, int d);
extern u8 *GetBoundedEntryField_0206db5c(int index);
extern void func_ov021_020a75d8(u8 *entry, int id);
extern void func_ov058_020d6c0c(u8 *entry);
extern int func_ov001_02063a38(void);
extern int func_ov035_020baf88(void);
extern int func_ov035_020bafc4(int index);
extern void func_ov032_020bb014(int index, int value);
extern int SNDi_LockMutex_020baf94(void);
extern void ConfigureChannelSlot_0206ca68(int a, int b, int c);

static inline void SetFieldZoneIndex(int zone)
{
    FieldGlobal *global = data_ov001_020a0460;
    if (!global->lockedBit) {
        global->zoneIndex = (u8)zone;
    }
}

int FieldObject_UpdateZoneTrigger_02081728(SceneObject *obj)
{
    SceneOwner *owner = obj->owner;
    BOOL enable = TRUE;
    int busy = func_ov001_02063838();
    u8 *entry;
    EntryCallback callback;
    int i;

    if (func_ov001_020642a0() != 0 || data_ov001_020a0460->state == 1) {
        enable = FALSE;
    }
    if (enable) {
        if (obj->flags & 2) {
            ActorSlot_SetFlag8ByIndex_02036120(obj->slotIndex, 1);
            obj->flags &= ~2;
            obj->drawFlags |= 0x30;
        }
    } else if (!(obj->flags & 2)) {
        ActorSlot_SetFlag8ByIndex_02036120(obj->slotIndex, 0);
        obj->flags |= 2;
        obj->drawFlags &= ~0x30;
        obj->flags &= ~1;
    }
    if (!(obj->flags & 2) && func_ov001_02063838() == 0 && func_ov001_0206dc4c(0) != NULL) {
        if (SceneObject_IsPointWithinOneUnit_02081a88(obj, func_ov001_0206dc4c(0))) {
            if (busy == 0 && !(obj->flags & 1)) {
                SpawnSoundSlot_0204da8c(0, 10, func_ov001_0207f810(obj), 0);
            }
            entry = GetBoundedEntryField_0206db5c(0);
            func_ov021_020a75d8(GetBoundedEntryField_0206db5c(0), *(u16 *)(*(u8 **)(entry + 0x1d4) + 4));
            entry = GetBoundedEntryField_0206db5c(0);
            callback = *(EntryCallback *)(entry + 0x200);
            if (callback != NULL) {
                callback(entry, 0);
            }
            for (i = 1; i < data_020608c8; i++) {
                func_ov058_020d6c0c(GetBoundedEntryField_0206db5c(i));
            }
            if (func_ov001_02063a38() == 6) {
                if (func_ov035_020baf88()) {
                    func_ov032_020bb014(1, func_ov035_020bafc4(1));
                }
                if (SNDi_LockMutex_020baf94()) {
                    func_ov032_020bb014(2, func_ov035_020bafc4(2));
                }
            }
            ConfigureChannelSlot_0206ca68(0, 1, 0);
            obj->flags |= 1;
            SetFieldZoneIndex(owner->zoneIndex);
        } else {
            obj->flags &= ~1;
        }
    }
    return 0;
}
