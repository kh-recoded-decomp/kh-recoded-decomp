#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[4];
    void *resource;
} StageEntry;

typedef struct SectionElement {
    u8 pad_00[4];
    int nodeIndex;
    u8 isLarge;
    u8 pad_09[2];
    u8 isHidden;
    u8 pad_0c[0xc];
    u8 variant;
} SectionElement;

typedef struct StageActor {
    u8 pad_000[0x288];
    u16 role : 2;
    u16 roleFlags : 14;
    u8 pad_28a[0x126];
    s16 parentId;
    u16 nextId;
} StageActor;

typedef struct StageManager {
    u8 pad_00000[0x18da0];
    u8 spawnCounts[0x40];
} StageManager;

typedef struct Spawner {
    s32 state;
    u16 active : 1;
    u16 flag1 : 3;
    u16 hidden : 1;
    u16 flag5 : 1;
    u16 large : 1;
    u16 flag7 : 9;
    u8 pad_06[3];
    u8 variant;
    u8 pad_0a[6];
    u16 busy;
    u8 pad_12[2];
    s16 entryId;
    u16 slotA;
    u16 slotB;
    u16 recordIndex;
    u8 pad_1c[0x184];
    u32 nextTime;
    u8 pad_1a4[0xc];
    s32 timer;
    u8 pad_1b4[8];
    s16 leaderId;
} Spawner;

extern StageEntry *GetStageEntry_0209c074(int id);
extern void func_ov001_02093188(Spawner *spawner);
extern void ScheduleSpawnerNextTime_02096928(Spawner *spawner, int delay);
extern u32 random_next_scaled_0202aa04(u32 range);
extern SectionElement *GetResourceSectionElement_020928b8(StageEntry *entry, int section, int index);
extern u16 ReleaseStageSlot_0209c008(int kind);
extern void *GetSmallTableEntry_0209c340(int index);
extern int GetOwnerTableEntryValue_02092950(StageEntry *entry, int section);
extern int func_ov001_020950f8(Spawner *spawner, StageEntry *entry, int index, int arg);
extern StageActor *GetStageActor_0209c040(int id);
extern s32 func_ov001_0208f018(void *resource, int index);
extern void AttachActorToStageNode_020911b4(StageActor *actor, int parentId, int node, int mode);
extern void func_ov001_02093330(Spawner *spawner);
extern void func_ov001_020925bc(Spawner *spawner, int state);
extern StageManager *func_ov001_0209c3c0(void);

void SpawnStageGroup_02094f60(Spawner *spawner, int unused1, int unused2, int arg)
{
    StageEntry *entry;
    StageActor *actor;
    u16 count;
    SectionElement *header;
    SectionElement *element;
    StageActor *link;
    StageManager *manager;
    int parentId;
    int actorId;
    u16 i;
    int node;

    parentId = 0;
    if (spawner != NULL && spawner->state == 1) {
        entry = GetStageEntry_0209c074(spawner->entryId);
        if (entry != NULL && spawner->busy == 0) {
            spawner->hidden = 0;
            func_ov001_02093188(spawner);
            ScheduleSpawnerNextTime_02096928(spawner, 0);
            spawner->nextTime += random_next_scaled_0202aa04(0xa000);
            header = GetResourceSectionElement_020928b8(entry, 0, 0);
            if (header != NULL) {
                spawner->slotA = ReleaseStageSlot_0209c008(8);
                spawner->slotB = ReleaseStageSlot_0209c008(9);
                spawner->variant = header->variant;
                if (header->isLarge) {
                    spawner->large = 1;
                }
                if (header->isHidden) {
                    spawner->hidden = 1;
                }
                if (spawner->recordIndex != 0xffff) {
                    GetSmallTableEntry_0209c340(spawner->recordIndex);
                }
                count = GetOwnerTableEntryValue_02092950(entry, 4);
                i = 0;
                if (count != 0) {
                    do {
                        element = GetResourceSectionElement_020928b8(entry, 4, i);
                        actorId = func_ov001_020950f8(spawner, entry, i, arg);
                        if (actorId == 0) {
                            break;
                        }
                        actor = GetStageActor_0209c040((s16)actorId);
                        if (i == 0) {
                            arg = 0;
                            parentId = actorId;
                        } else {
                            node = func_ov001_0208f018(entry->resource, element->nodeIndex);
                            if (node != 0) {
                                AttachActorToStageNode_020911b4(actor, parentId, node, 0);
                            }
                            for (link = GetStageActor_0209c040((s16)parentId); link != NULL; link = GetStageActor_0209c040((s16)link->nextId)) {
                                if (link->nextId == 0) {
                                    link->nextId = actorId;
                                    break;
                                }
                            }
                        }
                        actor->parentId = parentId;
                        if (actor->role == 2) {
                            spawner->leaderId = actorId;
                        }
                        i++;
                    } while (i < count);
                }
                func_ov001_02093330(spawner);
                spawner->timer = 0xf000;
                func_ov001_020925bc(spawner, 2);
                spawner->active = 1;
                if (spawner->recordIndex != 0xffff) {
                    manager = func_ov001_0209c3c0();
                    if (spawner->recordIndex < 0x40) {
                        manager->spawnCounts[spawner->recordIndex]++;
                    }
                }
            }
        }
    }
}

