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

extern StageManager *data_ov001_020a0508;
extern const VecFx32 data_02053438;
extern char data_ov001_020a0438[];
extern UnitTransformFunc data_020559c0[];

extern void UpdateStageBrightnessFade_0209b8e0(void);
extern StageEntry *CacheStageEntryValue_02099248(u32 id);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern EventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int SpawnStageObjectActor_02096ae0(EventRecord *record, SpawnParams *params, VecFx32 *position);
extern void func_ov001_020958f4(EventRecord *record, EventMessage *message);
extern FieldUnit *func_ov001_02087224(u32 id, u32 index);
extern void CacheEntry_SetActive_02087258(FieldUnit *unit, int active);
extern void func_ov016_020a69fc(FieldUnit *unit);
extern void func_ov016_020a6afc(FieldUnit *unit);
extern void SetFieldUnitPosition_020a6cc4(FieldUnit *unit, const VecFx32 *position);
extern void Obj_SetPosition_0203569c(void *object, const VecFx32 *position);
extern BOOL IsFieldUnitPhase6_020a6a64(FieldUnit *unit);
extern BOOL func_ov001_020983a0(const VecFx32 *position, FloorProbe *probe);
extern void *func_ov001_0208f27c(void *list);
extern StageCommand *BindDescriptor0_0208f268(void *list, void *node);
extern void *func_ov001_0208f28c(void *node);
extern BOOL IsCommandType8_02096224(StageCommand *command);
extern void func_ov001_02093e54(StageCommand *command);
extern u16 GetStageRowIndex_0209c228(StageCommand *command);
extern StageActor *GetStageActor_0209c040(int id);
extern BOOL IsCommandType4_0209838c(StageCommand *command);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02063a38(void);
extern u32 GetSmallRecordIndex_0209c248(StageCommand *command);
extern void ReleaseStageSlotEntry_0209c024(int kind, u32 index);
extern u16 IsSlotEntryUsed_0208f298(void *list, int slot);

static inline void PlaceUnit(FieldUnit *unit, const VecFx32 *position)
{
    unit->position = *position;
    Obj_SetPosition_0203569c(unit->object + 0x10, &unit->position);
    *unit->positionOut = unit->position;
    data_020559c0[unit->kind](&unit->positionOut, unit->transform);
}

static inline void DropSlotUnit(StageSlot *slot)
{
    if (slot != NULL && slot->unitIndex != 0) {
        FieldUnit *unit = func_ov001_02087224(slot->unitId, slot->unitIndex - 1);

        slot->position.y = 0x14000;
        PlaceUnit(unit, &slot->position);
        slot->state = 0;
    }
}

void UpdateStageManager_0209b950(u32 value)
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

    if (data_ov001_020a0508 == NULL) {
        return;
    }
    if (data_ov001_020a0508->flags & 0x40) {
        value = 0;
    }
    data_ov001_020a0508->inputValue = value;
    UpdateStageBrightnessFade_0209b8e0();
    manager = data_ov001_020a0508;
    entry = CacheStageEntryValue_02099248(1);
    if (data_ov001_020a0508->flags & 1) {
        manager->drift = data_02053438;
    } else if (entry != NULL) {
        if (VEC_Mag_01ff9f28(&manager->drift) > 4) {
            if (entry->applyDrift != NULL) {
                entry->applyDrift(entry, &manager->drift);
            }
            manager->drift.x = FixedPointMultiply12(manager->drift.x, 0xe66);
            manager->drift.y = FixedPointMultiply12(manager->drift.y, 0xe66);
            manager->drift.z = FixedPointMultiply12(manager->drift.z, 0xe66);
        } else {
            manager->drift = data_02053438;
        }
    }
    manager = data_ov001_020a0508;
    if (manager->spawnMode != 0) {
        if (manager->spawnRecordId != 0 && (record = GetStageEventRecord_0209c0ec(manager->spawnRecordId)) != NULL && manager->spawnMode == 1) {
            func_01ff88c4(&params, 0, sizeof(SpawnParams));
            params.ownerSlot = 0x2bd;
            params.attachActorId = record->linkedId;
            params.nodeName = data_ov001_020a0438;
            params.attach = 1;
            SpawnStageObjectActor_02096ae0(record, &params, NULL);
            record->health = record->maxHealth;
        }
        manager->spawnMode = 0;
        manager->spawnRecordId = 0;
    }
    if (data_ov001_020a0508->eventActive == 0) {
        data_ov001_020a0508->eventStarted = 0;
    }
    if (data_ov001_020a0508->eventRecordId != 0) {
        record = GetStageEventRecord_0209c0ec(data_ov001_020a0508->eventRecordId);
        func_01ff88c4(&message, 0, sizeof(EventMessage));
        message.mode = 1;
        message.flags |= 0x400;
        func_ov001_020958f4(record, &message);
        data_ov001_020a0508->eventStarted = 1;
        data_ov001_020a0508->eventRecordId = 0;
        data_ov001_020a0508->eventTimer = 0;
    }
    total = 0;
    data_ov001_020a0508->eventActive = 0;
    waiting = 0;
    for (i = 0; i < 16; i++) {
        slot = &data_ov001_020a0508->slots[i];
        if (slot->unitIndex != 0 && slot->active != 0) {
            total++;
            if (slot->state == 0) {
                waiting++;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        slot = &data_ov001_020a0508->slots[i];
        if (slot->unitIndex == 0) {
            continue;
        }
        if (total == waiting && slot->active != 0 && slot->state == 0) {
            slot->active = 0;
            unit = func_ov001_02087224(slot->unitId, slot->unitIndex - 1);
            slot->position = slot->home;
            CacheEntry_SetActive_02087258(unit, 1);
            func_ov016_020a69fc(unit);
            func_ov016_020a6afc(unit);
            SetFieldUnitPosition_020a6cc4(unit, &slot->position);
            PlaceUnit(unit, &slot->position);
            slot->state = 1;
        }
        if (slot->unitIndex == 0) {
            continue;
        }
        walker = func_ov001_02087224(0, slot->unitIndex - 1);
        switch (slot->state) {
        case 0:
            break;
        case 1:
            if (IsFieldUnitPhase6_020a6a64(walker)) {
                DropSlotUnit(slot);
            } else {
                if (func_ov001_020983a0(&slot->position, &probe)) {
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
            if (IsFieldUnitPhase6_020a6a64(walker)) {
                DropSlotUnit(slot);
            }
            break;
        }
    }
    func_01ff8830(data_ov001_020a0508->kindCounts, 0, sizeof(data_ov001_020a0508->kindCounts));
    node = func_ov001_0208f27c(data_ov001_020a0508->commandList);
    while (node != NULL) {
        command = BindDescriptor0_0208f268(data_ov001_020a0508->commandList, node);
        node = func_ov001_0208f28c(node);
        if (IsCommandType8_02096224(command)) {
            func_ov001_02093e54(command);
        } else if (command->active != 0) {
            if (command->kindIndex != 0xffff && command->active != 0) {
                data_ov001_020a0508->kindCounts[command->kindIndex]++;
            }
            if (command->kind == 0x3f) {
                data_ov001_020a0508->rowIndex = GetStageRowIndex_0209c228(command);
            }
        }
    }
    node = func_ov001_0208f27c(data_ov001_020a0508->triggerList);
    while (node != NULL) {
        command = BindDescriptor0_0208f268(data_ov001_020a0508->triggerList, node);
        node = func_ov001_0208f28c(node);
        if (command->actorId != 0 && (actor = GetStageActor_0209c040((s16)command->actorId)) != NULL) {
            release = IsCommandType4_0209838c(command);
            if (!release && command->recordId != 0 && (record = GetStageEventRecord_0209c0ec(command->recordId)) != NULL) {
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
                if (Session_Exists_02063a24()) {
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
                ReleaseStageSlotEntry_0209c024(4, GetSmallRecordIndex_0209c248(command));
            }
        }
    }
    node = func_ov001_0208f27c(data_ov001_020a0508->actorList);
    while (node != NULL) {
        actor = (StageActor *)BindDescriptor0_0208f268(data_ov001_020a0508->actorList, node);
        node = func_ov001_0208f28c(node);
        if (actor->slotIndex != 0 && !IsSlotEntryUsed_0208f298(data_ov001_020a0508->actorList, actor->slotIndex)) {
            actor->slotIndex = 0;
        }
    }
}
