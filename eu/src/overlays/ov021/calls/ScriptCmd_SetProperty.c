#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TaggedValue {
    s16 tag;
    s16 unknown02;
    s32 value;
} TaggedValue;

typedef struct PropertyCommand {
    TaggedValue target;
    TaggedValue property;
    TaggedValue argument;
} PropertyCommand;

typedef struct PropertyActor {
    u8 unknown000[0x14];
    u8 animationState[0x11c - 0x14];
    u8 indexedBytes[0x1d0 - 0x11c];
    u8 sequencer[0x26c - 0x1d0];
    u32 motionFlags : 31;
    u32 motionHighBit : 1;
    u16 spawnArg;
    u8 unknown272[2];
    fx32 value274;
    u8 unknown278[8];
    u16 animationId;
    u8 animationState282;
    u8 animationState283;
    u8 unknown284[4];
    u16 flags288Low : 2;
    u16 mode288 : 2;
    u16 unknown288Bits4 : 7;
    u16 flag288Bit11 : 1;
    u16 unknown288Bit12 : 1;
    u16 flag288Bit13 : 1;
    u16 flag288Bit14 : 1;
    u16 flag288Bit15 : 1;
    u16 mode28a : 2;
    u16 state28a : 3;
    u16 toggles28a : 3;
    u16 flag28aBit8 : 1;
    u16 unknown28aBits9 : 7;
    u16 unknown28cBits0 : 14;
    u16 flag28cBit14 : 1;
    u16 unknown28cBit15 : 1;
    u8 unknown28e[0x29c - 0x28e];
    fx32 value29c;
    u8 unknown2a0[8];
    fx32 value2a8;
    fx32 value2ac;
    u8 unknown2b0[0x10];
    VecFx32 position;
    VecFx32 previousPosition;
    VecFx32 nextPosition;
    u8 unknown2e4;
    u8 value2e5;
    u8 unknown2e6[0x31c - 0x2e6];
    fx32 value31c;
    u8 drawPriority;
    u8 unknown321[0x32c - 0x321];
    fx32 value32c;
    fx32 value330;
    fx32 value334;
    u8 unknown338[0x368 - 0x338];
    fx32 value368;
    fx32 value36c;
    fx32 value370;
    u8 unknown374[0x398 - 0x374];
    s32 value398;
    fx32 value39c;
    u8 unknown3a0[8];
    u16 motionId;
} PropertyActor;

typedef struct PropertyEvent {
    u8 unknown00[4];
    u16 flags04Low : 4;
    u16 flag04Bit4 : 1;
    u16 unknown04Bits5 : 7;
    u16 flag04Bit12 : 1;
    u16 flag04Bit13 : 1;
    u16 unknown04Bits14 : 2;
    u16 flags06Low : 10;
    u16 flag06Bit10 : 1;
    u16 flag06Bit11 : 1;
    u16 unknown06Bits12 : 4;
    u8 unknown08[5];
    u8 value0d;
    u16 kind;
    u16 actorId;
    u16 objectId;
    u16 unknown14;
    u16 motionId;
    u16 unknown18;
    u16 tableId;
    u8 unknown1c[0x70 - 0x1c];
    fx32 value70;
    fx32 value74;
    u8 unknown78[0x1bc - 0x78];
    u16 linkedActorId;
} PropertyEvent;

typedef struct PropertyController {
    u8 unknown00[8];
    u16 lowFlags : 2;
    u16 flagBit2 : 1;
    u16 unknownBit3 : 1;
    u16 flagBit4 : 1;
    u16 unknownBits5 : 11;
    u16 eventId;
    s16 actorId;
} PropertyController;

typedef struct PropertyFieldContext {
    PropertyEvent *event;
    PropertyController *controller;
    PropertyActor *actor;
} PropertyFieldContext;

typedef struct StageSpawnSettings {
    u16 ownerId;
    u16 spawnArg;
    s32 scaledValue;
    fx32 value08;
    u16 objectId;
    u16 argument;
    u16 mode;
    u16 unknown12;
    void *name;
} StageSpawnSettings;

typedef struct StageMoveSettings {
    u16 animationId;
    u16 unknown02;
    VecFx32 target;
    VecFx32 direction;
    s32 frames;
    s32 extra;
    u32 unknown24;
    fx32 moveSpeed;
    fx32 speed;
    s32 actorSpeed;
    u32 unknown34;
    u16 motionId;
    u16 unknown3a;
    u16 column;
    u16 row;
    u32 unknown40;
    u16 aimMode;
    u16 unknown46;
    s32 pitchDegrees;
    s32 yawDegrees;
    u32 unknown50;
} StageMoveSettings;

typedef struct SpawnPoint {
    u32 flags;
    VecFx32 offset;
    fx32 spread;
    u32 unknown14;
    s32 angle;
    u32 unknown1c;
} SpawnPoint;

typedef struct PropertyManager {
    u8 unknown00000[0x18e5c];
    fx32 value18e5c;
    u8 unknown18e60[0x18];
    SpawnPoint points[2];
    StageSpawnSettings spawn;
    u16 spawnPending;
    u16 nearestCommand;
    u16 argument18ed4;
    u16 unknown18ed6;
    StageMoveSettings move;
    u8 fadeStart;
    u8 fadeEnd;
    u16 unknown18f2e;
    s32 fadeTimer;
    fx32 fadeDuration;
} PropertyManager;

typedef struct SpawnParams {
    u16 ownerId;
    u16 objectId;
    u16 spawnArg;
    u16 argument;
    u16 hasName : 1;
    u16 modeOne : 1;
    u16 modeTwo : 1;
    u16 unknownBits3 : 13;
    u16 unknown0a;
    void *name;
} SpawnParams;

typedef struct EventPacket {
    u8 unknown00[0xc];
    fx32 value;
    u8 unknown10[0x1e];
    u16 animationId;
    u8 unknown30[0x18];
} EventPacket;

typedef struct RewardParams {
    u16 unknown00;
    u16 unknown02;
    u16 unknown04;
    u16 unknown06;
    u16 count;
    u16 unknown0a;
} RewardParams;

typedef struct LinkMoveCommand {
    u16 mode;
    u16 animationId;
    u16 motionId;
    u16 unknown06;
    VecFx32 target;
    u8 unknown14[0xc];
    s32 frames;
    s32 extra;
    fx32 moveSpeed;
} LinkMoveCommand;

typedef struct PropertyMotion {
    u16 state;
    s16 track;
    VecFx32 first;
    VecFx32 second;
    VecFx32 third;
} PropertyMotion;

typedef char PropertyActorValue29c[(u32)&((PropertyActor *)0)->value29c == 0x29c ? 1 : -1];
typedef char PropertyActorPosition[(u32)&((PropertyActor *)0)->position == 0x2c0 ? 1 : -1];
typedef char PropertyActorPriority[(u32)&((PropertyActor *)0)->drawPriority == 0x320 ? 1 : -1];
typedef char PropertyActorMotion[(u32)&((PropertyActor *)0)->motionId == 0x3a8 ? 1 : -1];
typedef char PropertyEventMotion[(u32)&((PropertyEvent *)0)->motionId == 0x16 ? 1 : -1];
typedef char PropertyEventValue[(u32)&((PropertyEvent *)0)->value70 == 0x70 ? 1 : -1];
typedef char PropertyEventLinked[(u32)&((PropertyEvent *)0)->linkedActorId == 0x1bc ? 1 : -1];
typedef char PropertyManagerSpawn[(u32)&((PropertyManager *)0)->spawn == 0x18eb8 ? 1 : -1];
typedef char PropertyManagerMove[(u32)&((PropertyManager *)0)->move == 0x18ed8 ? 1 : -1];
typedef char PropertyManagerFade[(u32)&((PropertyManager *)0)->fadeStart == 0x18f2c ? 1 : -1];
typedef char PropertyPacketSize[sizeof(EventPacket) == 0x48 ? 1 : -1];
typedef char PropertySpawnSize[sizeof(SpawnParams) == 0x10 ? 1 : -1];
typedef char PropertyMoveSize[sizeof(LinkMoveCommand) == 0x2c ? 1 : -1];

extern PropertyFieldContext gActiveFieldContext;
extern const VecFx32 gZeroVecFx32;
extern TaggedValue *ResolveTaggedValueRef(void *thread, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *value);
extern PropertyManager *GetStageManager(void);
extern PropertyEvent *ResolveEventRecordRef(void *thread, int ref);
extern PropertyActor *ResolveStageActorRef(void *thread, int ref);
extern PropertyEvent *GetStageEventRecord(u32 id);
extern PropertyActor *GetStageActor(s16 id);
extern PropertyMotion *GetStageMotionRecord(u16 id);
extern void SetLinkedActorPartHidden(PropertyActor *actor, int part, BOOL hidden);
extern void SetWalkerActive(PropertyActor *actor, int active);
extern s32 func_ov021_020b4ac4(void *thread, s32 offset);
extern void CacheActorNameIndex(PropertyActor *actor, const char *name);
extern void SetActorFacingDegrees(PropertyActor *actor, int degrees);
extern void SetActorTiltDegrees(PropertyActor *actor, int degrees);
extern void HandleSessionEffectEvent(int kind, fx32 value);
extern void SetBrightnessAndSyncMain(int brightness);
extern void IndexedBytes_SetAt10(void *container, int index, u8 value);
extern u16 GetLargeRecordIndex(PropertyActor *actor);
extern void func_01ff88c4(void *destination, u8 value, u32 size);
extern void MI_CpuFill8(void *destination, u32 value, u32 size);
extern int SpawnStageObjectActor(PropertyEvent *event, SpawnParams *params, VecFx32 *position);
extern PropertyController *GetStageController(u32 id);
extern void UpdateActorController_02098124(PropertyController *controller);
extern u16 FindNearestCommandEntry(PropertyEvent *event, int kind);
extern void ResetGroupCommandState(PropertyEvent *event);
extern void StartStageEventEffect(PropertyEvent *event);
extern void ReleaseEventLinkedEntries(PropertyEvent *event);
extern void ApplyHitToEnemyGroup(PropertyEvent *event, EventPacket *packet);
extern void func_ov001_02095904(PropertyEvent *event, u16 kind);
extern void *GetSmallTableEntry(u16 id);
extern void func_ov001_020664f0(int kind, int unknown, const VecFx32 *position, int option);
extern u32 random_next_scaled(u32 limit);
extern void SpawnRewardOrbs(RewardParams *params, const VecFx32 *position, int option);
extern void MoveLinkedActor_020afdc8(PropertyEvent *event, int unused, u16 column, u16 row, LinkMoveCommand *command);
extern void BlendToAnimationTrack(void *animation, u16 track, void *table, s16 index, int frame);
extern fx32 ApplyActorScaleFactors(PropertyActor *actor);
extern fx32 VEC_Mag(const VecFx32 *vector);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov001_02068968(int kind, int index);
extern void RunGridPathCommand(PropertyEvent *event, u16 property);
extern void BindLinkSlotTable(PropertyEvent *event, u16 index);
extern void ClaimSlot(u32 *table, u32 slot);
extern void ReleaseSlot(u32 *table, u32 slot);
extern void ForwardToFirstType11Entry(u32 index, fx32 value);
extern void ClearSessionPackedBit(u32 flag);
extern void SetSessionFlag(u32 flag);
extern void RunOverrideTrack(void *sequencer, u16 track);


#pragma opt_propagation off
s32 ScriptCmd_SetProperty(void *thread, PropertyCommand *command)
{
    EventPacket valuePacket;
    EventPacket copiedValuePacket;
    SpawnParams spawnParams;
    RewardParams rewards;
    LinkMoveCommand moveCommand;
    PropertyFieldContext savedContext;
    VecFx32 zero;
    TaggedValue *target = ResolveTaggedValueRef(thread, &command->target);
    TaggedValue *property = ResolveTaggedValueRef(thread, &command->property);
    TaggedValue *argument = ResolveTaggedValueRef(thread, &command->argument);
    PropertyManager *manager = GetStageManager();
    PropertyEvent *event = ResolveEventRecordRef(thread, target->value);
    PropertyActor *actor = ResolveStageActorRef(thread, target->value);
    PropertyController *controller = gActiveFieldContext.controller;
    PropertyMotion *motion;
    u16 overrideTrack = 0;
    BOOL handled = FALSE;

    if (actor != NULL) {
        switch (property->value) {
        case 0xac:
            actor->flag288Bit11 = (u16)TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x98:
            actor->value368 += TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x99:
            actor->value36c += TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x9a:
            actor->value370 += TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x8d:
            SetLinkedActorPartHidden(actor, (u16)TaggedValueToInt(argument), FALSE);
            handled = TRUE;
            break;
        case 0x8e:
            SetLinkedActorPartHidden(actor, (u16)TaggedValueToInt(argument), TRUE);
            handled = TRUE;
            break;
        case 0xab:
            SetWalkerActive(actor, TaggedValueToInt(argument));
            handled = TRUE;
            break;
        case 0xa7:
            actor->flag28cBit14 = (u16)TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0xa5:
            CacheActorNameIndex(actor, (const char *)func_ov021_020b4ac4(thread, argument->value));
            handled = TRUE;
            break;
        case 0xa4:
            actor->value2e5 = TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x89:
            actor->mode288 = (u16)TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x17:
            overrideTrack = argument->value;
            handled = TRUE;
            break;
        case 0x06:
            actor->spawnArg = TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x7e:
            actor->value32c = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x7f:
            actor->value330 = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x6b:
            actor->value31c = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x7c:
            actor->drawPriority = TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x7b:
            actor->value398 = TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x7a:
            actor->value39c = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x6f:
            actor->flag28aBit8 = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x6c:
            actor->animationId = TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x69:
            actor->flag288Bit15 = (u16)TaggedValueToInt(argument);
            handled = TRUE;
            break;
        case 0x1b:
            actor->mode28a = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x13:
            actor->value29c = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x14:
            actor->value2ac = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x15:
            actor->value2a8 = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x30:
            actor->flag288Bit13 = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x19:
            actor->motionFlags |= 1;
            handled = TRUE;
            break;
        case 0x34:
            actor->value334 = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x31: {
            int bits;
            if (argument->value != 0) {
                bits = actor->toggles28a | 1;
            } else {
                bits = actor->toggles28a & ~1;
            }
            actor->toggles28a = (u16)bits;
            handled = TRUE;
            break;
        }
        case 0x32: {
            int bits;
            if (argument->value != 0) {
                bits = actor->toggles28a | 2;
            } else {
                bits = actor->toggles28a & ~2;
            }
            actor->toggles28a = (u16)bits;
            handled = TRUE;
            break;
        }
        case 0x33: {
            int bits;
            if (argument->value != 0) {
                bits = actor->toggles28a | 4;
            } else {
                bits = actor->toggles28a & ~4;
            }
            actor->toggles28a = (u16)bits;
            handled = TRUE;
            break;
        }
        case 0x35:
            actor->motionId = argument->value;
            handled = TRUE;
            break;
        case 0x67:
            actor->flag288Bit14 = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x58:
            SetActorFacingDegrees(actor, TaggedValueToFixed(argument));
            handled = TRUE;
            break;
        case 0x57:
            SetActorTiltDegrees(actor, TaggedValueToFixed(argument));
            handled = TRUE;
            break;
        case 0x5b:
            actor->state28a = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x5c:
            actor->mode28a = (u16)argument->value;
            handled = TRUE;
            break;
        case 0x5d:
            actor->value274 = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x5e:
            HandleSessionEffectEvent(2, TaggedValueToFixed(argument));
            handled = TRUE;
            break;
        case 0x66:
            SetBrightnessAndSyncMain(argument->value);
            handled = TRUE;
            break;
        case 0x92:
            IndexedBytes_SetAt10(actor->indexedBytes, 3, TaggedValueToInt(argument));
            handled = TRUE;
            break;
        case 0x37:
            manager->spawn.scaledValue = argument->value << 12;
            handled = TRUE;
            break;
        case 0x38:
            manager->spawn.value08 = TaggedValueToFixed(argument);
            handled = TRUE;
            break;
        case 0x39:
            manager->spawn.argument = GetLargeRecordIndex(ResolveStageActorRef(thread, argument->value));
            handled = TRUE;
            break;
        case 0x3a:
            manager->spawn.name = (void *)func_ov021_020b4ac4(thread, argument->value);
            handled = TRUE;
            break;
        case 0x3b:
            manager->spawn.mode = argument->value;
            handled = TRUE;
            break;
        case 0x3c:
            manager->spawn.objectId = argument->value;
            handled = TRUE;
            break;
        case 0x36:
            manager->spawn.ownerId = argument->value;
            handled = TRUE;
            break;
        case 0x8c:
            manager->spawn.spawnArg = argument->value;
            handled = TRUE;
            break;
        case 0x3e:
            func_01ff88c4(&manager->spawn, 0, sizeof(manager->spawn));
            handled = TRUE;
            break;
        case 0x3f: {
            PropertyController *spawnedController;
            if (event == NULL && controller != NULL) {
                event = GetStageEventRecord(controller->eventId);
            }
            func_01ff88c4(&spawnParams, 0, sizeof(spawnParams));
            spawnParams.objectId = manager->spawn.objectId;
            spawnParams.spawnArg = manager->spawn.spawnArg;
            spawnParams.argument = manager->spawn.argument;
            spawnParams.name = manager->spawn.name;
            spawnParams.hasName = spawnParams.name != NULL;
            spawnParams.modeOne = manager->spawn.mode == 1;
            spawnParams.modeTwo = manager->spawn.mode == 2;
            spawnParams.ownerId = manager->spawn.ownerId;
            spawnedController = GetStageController(SpawnStageObjectActor(event, &spawnParams, NULL));
            if (spawnedController == NULL) {
                return 0;
            }
            UpdateActorController_02098124(spawnedController);
            func_01ff88c4(&manager->spawn, 0, sizeof(manager->spawn));
            handled = TRUE;
            break;
        }
        case 0x41:
            manager->spawnPending = 1;
            handled = TRUE;
            break;
        case 0x42:
            manager->argument18ed4 = argument->value;
            handled = TRUE;
            break;
        case 0x40:
            manager->nearestCommand = TaggedValueToInt(argument);
            if (manager->nearestCommand == 0) {
                manager->nearestCommand = FindNearestCommandEntry(event, 1);
            }
            handled = TRUE;
            break;
        }
        if (handled) {
            goto runOverride;
        }
    }
    {
        if (controller != NULL) {
            switch (property->value) {
            case 0x97:
                controller->flagBit2 = (u16)TaggedValueToInt(argument);
                handled = TRUE;
                break;
            case 0xa6:
                controller->flagBit4 = (u16)TaggedValueToInt(argument);
                handled = TRUE;
                break;
            }
        }
        if (event != NULL) {
            if (event->motionId == 0) {
                return 0;
            }
            motion = GetStageMotionRecord(event->motionId);
            switch (property->value) {
            case 0x12:
                event->flag04Bit12 = (u16)argument->value;
                handled = TRUE;
                break;
            case 0x6a:
                event->flag04Bit13 = (u16)argument->value;
                handled = TRUE;
                break;
            case 0x10:
                event->value0d = argument->value;
                handled = TRUE;
                break;
            case 0x0c:
                event->flag04Bit4 = (u16)argument->value;
                handled = TRUE;
                break;
            case 0x16:
                event->value70 = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x9c:
                event->flag06Bit11 = (u16)TaggedValueToInt(argument);
                handled = TRUE;
                break;
            case 0x8a:
                ResetGroupCommandState(event);
                handled = TRUE;
                break;
            case 0x1e:
                StartStageEventEffect(event);
                handled = TRUE;
                break;
            case 0x1f:
                ReleaseEventLinkedEntries(event);
                handled = TRUE;
                break;
            case 0x72:
                func_01ff88c4(&valuePacket, 0, sizeof(valuePacket));
                valuePacket.animationId = actor->animationId;
                valuePacket.value = TaggedValueToFixed(argument);
                ApplyHitToEnemyGroup(event, &valuePacket);
                handled = TRUE;
                break;
            case 0x80:
                func_ov001_02095904(event, TaggedValueToInt(argument));
                handled = TRUE;
                break;
            case 0x84: {
                void *entry = GetSmallTableEntry(event->tableId);
                if (event != NULL && entry != NULL) {
                    if (event->kind == 0x2b) {
                        func_ov001_020664f0(5, 0, &actor->position, 0);
                    } else if (event->kind == 0x3f) {
                        RewardParams *params = &rewards;
                        params->unknown00 = 0;
                        params->unknown02 = 0;
                        params->unknown04 = 0;
                        params->unknown06 = 0;
                        params->count = 0;
                        params->unknown0a = 0;
                        params->count = random_next_scaled(40) + 10;
                        SpawnRewardOrbs(params, &actor->position, 0);
                    } else {
                        event->flag06Bit10 = 1;
                    }
                }
                handled = TRUE;
                break;
            }
            case 0x54:
                manager->move.animationId = TaggedValueToInt(argument);
                handled = TRUE;
                break;
            case 0x43:
                manager->move.aimMode = argument->value;
                handled = TRUE;
                break;
            case 0x47:
                manager->move.motionId = argument->value;
                handled = TRUE;
                break;
            case 0x44:
                manager->move.target.x = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x45:
                manager->move.target.y = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x46:
                manager->move.target.z = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x4b:
                manager->move.speed = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x4d:
                manager->move.frames = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x4e:
                manager->move.extra = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x52:
                manager->move.column = argument->value;
                handled = TRUE;
                break;
            case 0x53:
                manager->move.row = argument->value;
                handled = TRUE;
                break;
            case 0x4f:
                manager->move.moveSpeed = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x49:
                manager->move.pitchDegrees = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x4a:
                manager->move.yawDegrees = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x8f:
                manager->move.unknown34 = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x4c:
                manager->move.actorSpeed = TaggedValueToFixed(argument);
                handled = TRUE;
                break;
            case 0x55:
                func_01ff88c4(&manager->move, 0, sizeof(manager->move));
                handled = TRUE;
                break;
            case 0x56: {
                PropertyController *activeController = gActiveFieldContext.controller;
                if (event == NULL && activeController != NULL) {
                    event = GetStageEventRecord(activeController->eventId);
                }
                MI_CpuFill8(&moveCommand, 0, sizeof(moveCommand));
                moveCommand.mode = manager->move.aimMode;
                moveCommand.motionId = manager->move.motionId;
                moveCommand.frames = manager->move.frames;
                moveCommand.extra = manager->move.extra;
                moveCommand.moveSpeed = manager->move.moveSpeed;
                moveCommand.animationId = manager->move.animationId;
                MoveLinkedActor_020afdc8(event, 0, manager->move.column,
                                  manager->move.row, &moveCommand);
                handled = TRUE;
                break;
            }
            case 0x87:
                if (event->linkedActorId != 0) {
                    PropertyActor *linked = GetStageActor(event->linkedActorId);
                    if (linked != NULL) {
                        motion->state = 1;
                        motion->track = argument->value;
                        zero = gZeroVecFx32;
                        motion->first = zero;
                        motion->second = zero;
                        motion->third = zero;
                        linked->animationState282 = 0;
                        linked->animationState283 = 0;
                        BlendToAnimationTrack(linked->animationState, 0, NULL,
                                              motion->track, 0);
                    }
                }
                handled = TRUE;
                break;
            case 0x88:
                if (event->linkedActorId != 0) {
                    PropertyActor *linked = GetStageActor(event->linkedActorId);
                    if (linked != NULL) {
                        fx32 scale = ApplyActorScaleFactors(linked);
                        if (scale != 0) {
                            actor->value29c = FX_Div(VEC_Mag(&motion->third), scale);
                        } else {
                            actor->value29c = 0;
                        }
                        VEC_Add(&actor->position, &motion->third, &actor->previousPosition);
                        actor->nextPosition = actor->previousPosition;
                    }
                }
                handled = TRUE;
                break;
            case 0x68:
                func_ov001_02068968(0, event->objectId - 1);
                break;
            case 0x61:
                RunGridPathCommand(event, property->value);
                break;
            case 0x62:
                RunGridPathCommand(event, property->value);
                break;
            case 0x63:
                RunGridPathCommand(event, property->value);
                break;
            case 0x74:
                BindLinkSlotTable(event, argument->value);
                break;
            case 0x78:
                ClaimSlot((u32 *)motion, argument->value);
                break;
            case 0x79:
                ReleaseSlot((u32 *)motion, argument->value);
                break;
            case 0x90: {
                PropertyEvent *other = ResolveEventRecordRef(thread, TaggedValueToInt(argument));
                if (event != NULL && other != NULL) {
                    fx32 previous = event->value70;
                    event->value70 = other->value70;
                    event->value74 = other->value74;
                    if (event->kind == 0x3d && previous > 0 && event->value70 <= 0) {
                        func_01ff88c4(&copiedValuePacket, 0, sizeof(copiedValuePacket));
                        copiedValuePacket.value = event->value74;
                        event->value70 = 1;
                        ApplyHitToEnemyGroup(event, &copiedValuePacket);
                    }
                }
                break;
            }
            case 0x96: {
                u32 index = random_next_scaled(4) & 3;
                ForwardToFirstType11Entry(index, TaggedValueToFixed(argument));
                break;
            }
            case 0x93:
                if (TaggedValueToInt(argument) != 0) {
                    SetSessionFlag(0x3713);
                } else {
                    ClearSessionPackedBit(0x3713);
                }
                break;
            case 0xa8:
                SetSessionFlag(0x380b);
                break;
            }
            if (handled) {
                goto runOverride;
            }
        }
        if (manager != NULL) {
            switch (property->value) {
            case 0xa2:
                manager->points[0].flags = TaggedValueToInt(argument);
                break;
            case 0xa3:
                manager->points[0].offset.x = TaggedValueToInt(argument);
                break;
            case 0x1d:
                manager->value18e5c = TaggedValueToFixed(argument);
                break;
            case 0xa0:
                manager->fadeStart = 0;
                manager->fadeEnd = 16;
                manager->fadeTimer = 0;
                manager->fadeDuration = TaggedValueToFixed(argument);
                break;
            case 0xa1:
                manager->fadeStart = 16;
                manager->fadeEnd = 0;
                manager->fadeTimer = 0;
                manager->fadeDuration = TaggedValueToFixed(argument);
                break;
            }
        }
    }
runOverride:
    if (overrideTrack != 0) {
        savedContext = gActiveFieldContext;
        RunOverrideTrack(actor->sequencer, overrideTrack);
        gActiveFieldContext = savedContext;
    }
    return 0;
}
