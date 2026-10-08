#include "nitro/types.h"

typedef void (*EntityCallback)(void);

typedef struct Entity {
    u8 pad_000[0x1e0];
    EntityCallback shutdownCallback;
    u8 pad_1e4[0x1e8 - 0x1e4];
    EntityCallback drawCallback;
    u8 pad_1ec[0x1f4 - 0x1ec];
    EntityCallback rewardCallback;
    EntityCallback updateCallback;
    u8 pad_1fc[0x20c - 0x1fc];
    EntityCallback modeCallback;
    EntityCallback angleCallback;
    u8 pad_214[0x218 - 0x214];
    EntityCallback stepCallback;
    u8 pad_21c[0x6bc - 0x21c];
    s32 targets[4];
    u8 pad_6cc[0x9ac - 0x6cc];
    u64 stateFlags;
    u8 kind;
    u8 pad_9b5[3];
    s32 unk_9b8;
    u8 pad_9bc[0x10e8 - 0x9bc];
    EntityCallback actionCallback;
    EntityCallback specialCallback;
    u8 pad_10f0[0x10f4 - 0x10f0];
    EntityCallback thinkCallback;
    u8 pad_10f8[0x10fc - 0x10f8];
    EntityCallback handleCallback;
    u8 pad_1100[0x125c - 0x1100];
    s32 unk_125c;
} Entity;

extern void InstallActorCallbacks(Entity *entity);
extern int func_ov001_02063a38(void);
extern BOOL func_ov001_0206e31c(void);
extern void ShutdownOverlay053(void);
extern void RequestOverlay053ActorState(void);
extern void SetEntityModeHideSubModels(void);
extern void StartAreaMusic(void);
extern void DrawCarriedActor(void);
extern void SetPanelModelAngle(void);
extern void ChangeCarriedActorState(void);
extern void RefreshScrollListLayout(void);
extern void LoadOverlay053EntityResources(void);
extern void UpdateModelBlinkEffect(void);
extern void Entity_HandleSpecialAction(void);
extern void func_ov010_020a1998(void);

void InitOverlay053Entity(Entity *entity, u8 kind)
{
    int i;

    entity->kind = kind;
    entity->unk_9b8 = 0;
    entity->stateFlags = 0;
    entity->unk_125c = 0;
    for (i = 0; i < 4; i++) {
        entity->targets[i] = -1;
    }
    InstallActorCallbacks(entity);
    entity->shutdownCallback = ShutdownOverlay053;
    entity->updateCallback = RequestOverlay053ActorState;
    entity->modeCallback = SetEntityModeHideSubModels;
    entity->stepCallback = StartAreaMusic;
    if (func_ov001_02063a38() == 4) {
        entity->drawCallback = DrawCarriedActor;
        entity->angleCallback = SetPanelModelAngle;
        entity->specialCallback = ChangeCarriedActorState;
    } else if (func_ov001_02063a38() == 6) {
        entity->rewardCallback = RefreshScrollListLayout;
    }
    entity->actionCallback = LoadOverlay053EntityResources;
    entity->thinkCallback = UpdateModelBlinkEffect;
    if (func_ov001_0206e31c()) {
        entity->handleCallback = Entity_HandleSpecialAction;
        entity->specialCallback = func_ov010_020a1998;
    }
}
