#pragma thumb on
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageSlot {
    u16 active;
    u16 state;
    u16 unitId;
    u16 unitIndex;
    VecFx32 home;
    VecFx32 position;
    fx32 floor;
    u8 pad_24[4];
} StageSlot;

typedef struct StageManager {
    u32 flags;
    u8 pad_00004[0x18814 - 0x4];
    StageSlot slots[16];
    u8 pad_18a94[0x18d7c - 0x18a94];
    void *commandList;
    u8 pad_18d80[4];
    void *actorList;
    void *triggerList;
    u8 pad_18d8c[0x18da0 - 0x18d8c];
    u8 kindCounts[0x40];
    u32 inputValue;
    u8 pad_18de4[0x18e50 - 0x18de4];
    VecFx32 drift;
    u8 pad_18e5c[0x18ed0 - 0x18e5c];
    u16 spawnMode;
    u16 spawnRecordId;
    u8 pad_18ed4[0x18f38 - 0x18ed4];
    u8 eventActive;
    u8 eventStarted;
    u16 eventRecordId;
    u32 eventTimer;
    u8 pad_18f40[0x18f48 - 0x18f40];
    u16 rowIndex;
} StageManager;

typedef struct StageEntry {
    u8 pad_000[0x214];
    void (*applyDrift)(struct StageEntry *entry, VecFx32 *drift);
} StageEntry;

typedef struct EventRecord {
    u32 type;
    u16 flags4_low : 13;
    u16 defeated : 1;
    u16 flags4_high : 2;
    u16 flags6_low : 2;
    u16 armed : 1;
    u16 flags6_high : 13;
    u8 pad_08;
    u8 category;
    u8 pad_0a[4];
    u16 kind;
    u16 linkedId;
    u8 pad_12[0x70 - 0x12];
    s32 health;
    s32 maxHealth;
} EventRecord;

typedef struct StageCommand {
    u8 pad_00[8];
    u16 flags_low : 2;
    u16 keepArmed : 1;
    u16 keepDefeated : 1;
    u16 flags_high : 12;
    u16 recordId;
    u16 actorId;
    u16 kind;
    u16 active;
    u8 pad_12[8];
    u16 kindIndex;
} StageCommand;

typedef struct StageActor {
    u8 pad_000[0x3ac];
    u16 slotIndex;
} StageActor;

typedef struct FieldUnit {
    u8 pad_00[8];
    u8 *object;
    u8 pad_0c[4];
    VecFx32 *positionOut;
    u8 transform[0x18];
    s32 kind;
    u8 pad_30[8];
    VecFx32 position;
} FieldUnit;

typedef struct SpawnParams {
    u16 walkerKind;
    u16 ownerSlot;
    u16 spawnArg;
    u16 attachActorId;
    u16 attach : 1;
    u16 align : 1;
    u16 attachDefault : 1;
    u16 unused : 13;
    u16 pad_0a;
    const char *nodeName;
} SpawnParams;

typedef struct EventMessage {
    u8 pad_00[0xc];
    u32 mode;
    u8 pad_10[0x18];
    u16 flags;
    u8 pad_2a[0x48 - 0x2a];
} EventMessage;

typedef struct FloorProbe {
    u32 hit;
    fx32 height;
    u8 pad_08[4];
} FloorProbe;

typedef void (*UnitTransformFunc)(VecFx32 **positionOut, u8 *transform);

extern StageManager *data_ov001_020a0528;
extern const VecFx32 data_0205344c;
extern char data_ov001_020a0458[];
extern UnitTransformFunc gCollisionBoundsDispatch[];

extern void UpdateStageBrightnessFade(void);
extern StageEntry *CacheStageEntryValue(u32 id);
extern fx32 VEC_Mag(const VecFx32 *vec);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern EventRecord *GetStageEventRecord(u32 id);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int SpawnStageObjectActor(EventRecord *record, SpawnParams *params, VecFx32 *position);
extern void func_ov001_0209591c(EventRecord *record, EventMessage *message);
extern FieldUnit *func_ov001_0208724c(u32 id, u32 index);
extern void CacheEntry_SetActive(FieldUnit *unit, int active);
extern void func_ov016_020a6a1c(FieldUnit *unit);
extern void ResetUnitToBasePosition(FieldUnit *unit);
extern void SetFieldUnitPosition(FieldUnit *unit, const VecFx32 *position);
extern void Obj_SetPosition(void *object, const VecFx32 *position);
extern BOOL IsFieldUnitPhase6(FieldUnit *unit);
extern BOOL func_ov001_020983c8(const VecFx32 *position, FloorProbe *probe);
extern void *func_ov001_0208f2a4(void *list);
extern StageCommand *BindDescriptor0(void *list, void *node);
extern void *func_ov001_0208f2b4(void *node);
extern BOOL IsCommandType8(StageCommand *command);
extern void ReleaseEventResources(StageCommand *command);
extern u16 GetStageRowIndex(StageCommand *command);
extern StageActor *GetStageActor(int id);
extern BOOL IsCommandType4(StageCommand *command);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern u32 GetSmallRecordIndex(StageCommand *command);
extern void ReleaseStageSlotEntry(int kind, u32 index);
extern u16 IsSlotEntryUsed(void *list, int slot);

static inline void PlaceUnit(FieldUnit *unit, const VecFx32 *position)
{
    unit->position = *position;
    Obj_SetPosition(unit->object + 0x10, &unit->position);
    *unit->positionOut = unit->position;
    gCollisionBoundsDispatch[unit->kind](&unit->positionOut, unit->transform);
}

static inline void DropSlotUnit(StageSlot *slot)
{
    if (slot != NULL && slot->unitIndex != 0) {
        FieldUnit *unit = func_ov001_0208724c(slot->unitId, slot->unitIndex - 1);

        slot->position.y = 0x14000;
        PlaceUnit(unit, &slot->position);
        slot->state = 0;
    }
}

void UpdateStageManager(u32 value)
{
    EventMessage message;
    SpawnParams params;
    FloorProbe probe;
    StageActor *actor;
    u16 waiting;
    u16 total;
    StageManager *manager;
    StageEntry *entry;
    EventRecord *record;
    StageSlot *slot;
    FieldUnit *unit;
    FieldUnit *walker;
    void *node;
    StageCommand *command;
    int release;
    int i;

    if (data_ov001_020a0528 == NULL) {
        return;
    }
    if (data_ov001_020a0528->flags & 0x40) {
        value = 0;
    }
    data_ov001_020a0528->inputValue = value;
    UpdateStageBrightnessFade();
    manager = data_ov001_020a0528;
    entry = CacheStageEntryValue(1);
    if (data_ov001_020a0528->flags & 1) {
        manager->drift = data_0205344c;
    } else if (entry != NULL) {
        if (VEC_Mag(&manager->drift) > 4) {
            if (entry->applyDrift != NULL) {
                entry->applyDrift(entry, &manager->drift);
            }
            manager->drift.x = FX_Mul(manager->drift.x, 0xe66);
            manager->drift.y = FX_Mul(manager->drift.y, 0xe66);
            manager->drift.z = FX_Mul(manager->drift.z, 0xe66);
        } else {
            manager->drift = data_0205344c;
        }
    }
    manager = data_ov001_020a0528;
    if (manager->spawnMode != 0) {
        if (manager->spawnRecordId != 0 && (record = GetStageEventRecord(manager->spawnRecordId)) != NULL && manager->spawnMode == 1) {
            func_01ff88c4(&params, 0, sizeof(SpawnParams));
            params.ownerSlot = 0x2bd;
            params.attachActorId = record->linkedId;
            params.nodeName = data_ov001_020a0458;
            params.attach = 1;
            SpawnStageObjectActor(record, &params, NULL);
            record->health = record->maxHealth;
        }
        manager->spawnMode = 0;
        manager->spawnRecordId = 0;
    }
    if (data_ov001_020a0528->eventActive == 0) {
        data_ov001_020a0528->eventStarted = 0;
    }
    if (data_ov001_020a0528->eventRecordId != 0) {
        record = GetStageEventRecord(data_ov001_020a0528->eventRecordId);
        func_01ff88c4(&message, 0, sizeof(EventMessage));
        message.mode = 1;
        message.flags |= 0x400;
        func_ov001_0209591c(record, &message);
        data_ov001_020a0528->eventStarted = 1;
        data_ov001_020a0528->eventRecordId = 0;
        data_ov001_020a0528->eventTimer = 0;
    }
    total = 0;
    data_ov001_020a0528->eventActive = 0;
    waiting = 0;
    for (i = 0; i < 16; i++) {
        slot = &data_ov001_020a0528->slots[i];
        if (slot->unitIndex != 0 && slot->active != 0) {
            total++;
            if (slot->state == 0) {
                waiting++;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        slot = &data_ov001_020a0528->slots[i];
        if (slot->unitIndex == 0) {
            continue;
        }
        if (total == waiting && slot->active != 0 && slot->state == 0) {
            slot->active = 0;
            unit = func_ov001_0208724c(slot->unitId, slot->unitIndex - 1);
            slot->position = slot->home;
            CacheEntry_SetActive(unit, 1);
            func_ov016_020a6a1c(unit);
            ResetUnitToBasePosition(unit);
            SetFieldUnitPosition(unit, &slot->position);
            PlaceUnit(unit, &slot->position);
            slot->state = 1;
        }
        if (slot->unitIndex == 0) {
            continue;
        }
        walker = func_ov001_0208724c(0, slot->unitIndex - 1);
        switch (slot->state) {
        case 0:
            break;
        case 1:
            if (IsFieldUnitPhase6(walker)) {
                DropSlotUnit(slot);
            } else {
                if (func_ov001_020983c8(&slot->position, &probe)) {
                    slot->floor = probe.height;
                }
                slot->position.y -= 0x800;
                if (slot->position.y < slot->floor) {
                    slot->position.y = slot->floor;
                }
                PlaceUnit(walker, &slot->position);
            }
            break;
        case 2:
            if (IsFieldUnitPhase6(walker)) {
                DropSlotUnit(slot);
            }
            break;
        }
    }
    MI_CpuFill8(data_ov001_020a0528->kindCounts, 0, sizeof(data_ov001_020a0528->kindCounts));
    node = func_ov001_0208f2a4(data_ov001_020a0528->commandList);
    while (node != NULL) {
        command = BindDescriptor0(data_ov001_020a0528->commandList, node);
        node = func_ov001_0208f2b4(node);
        if (IsCommandType8(command)) {
            ReleaseEventResources(command);
        } else if (command->active != 0) {
            if (command->kindIndex != 0xffff && command->active != 0) {
                data_ov001_020a0528->kindCounts[command->kindIndex]++;
            }
            if (command->kind == 0x3f) {
                data_ov001_020a0528->rowIndex = GetStageRowIndex(command);
            }
        }
    }
    node = func_ov001_0208f2a4(data_ov001_020a0528->triggerList);
    while (node != NULL) {
        command = BindDescriptor0(data_ov001_020a0528->triggerList, node);
        node = func_ov001_0208f2b4(node);
        if (command->actorId != 0 && (actor = GetStageActor((s16)command->actorId)) != NULL) {
            release = IsCommandType4(command);
            if (!release && command->recordId != 0 && (record = GetStageEventRecord(command->recordId)) != NULL) {
                int phase;

                if (actor->slotIndex != 0) {
                    if ((record->category != 4 || record->kind == 9 || record->kind == 0x2e || record->kind == 0x2f || record->kind == 0x41 || record->kind == 0x4f)
                        && ((record->health <= 0 && !record->defeated) || record->linkedId == 0)) {
                        release = command->keepDefeated ? 0 : 1;
                    }
                    if (!release && record->type == 5 && record->armed) {
                        release = command->keepArmed ? 0 : 1;
                    }
                }
                if (func_ov001_02063a24()) {
                    phase = func_ov001_02063a38();
                } else {
                    phase = 0;
                }
                if (phase == 6 && !release) {
                    if (record->type == 0xb) {
                        release = 1;
                    }
                    if (record->type == 6) {
                        release = 1;
                    }
                }
            }
            if (release) {
                ReleaseStageSlotEntry(4, GetSmallRecordIndex(command));
            }
        }
    }
    node = func_ov001_0208f2a4(data_ov001_020a0528->actorList);
    while (node != NULL) {
        actor = (StageActor *)BindDescriptor0(data_ov001_020a0528->actorList, node);
        node = func_ov001_0208f2b4(node);
        if (actor->slotIndex != 0 && !IsSlotEntryUsed(data_ov001_020a0528->actorList, actor->slotIndex)) {
            actor->slotIndex = 0;
        }
    }
}
