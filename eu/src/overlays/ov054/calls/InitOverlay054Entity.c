<<<<<<< HEAD
#define FX_Div_020d24dc func_ov054_020d24fc
#define InitOverlay054Entity_020d21f4 InitOverlay054Entity
#define LoadMenuSoundArcs_020d2688 LoadMenuSoundArcs
#define RefreshModeMenuHighlights_020d2aa0 RefreshModeMenuHighlights
#define ShutdownOverlay054_020d2520 ShutdownOverlay054
#define data_ov001_020a0460 data_ov001_020a0480
#define func_0204f768 GetOverlaySelectionRecord
#define func_ov052_020cce6c func_ov052_020cce8c
#define func_ov054_020d2320 LoadOverlay054EntityResources
#define func_ov054_020d24ec func_ov054_020d250c
#define func_ov054_020d2554 RequestOverlay054ActorState
#define func_ov054_020d2774 func_ov054_020d2794
#define func_ov054_020d2dac func_ov054_020d2dcc
#define func_ov058_020d7e30 LoadSceneModelResources
#include "src/ov054/object_factory/InitOverlay054Entity_020d21f4.c"
=======
#include "nitro/types.h"

typedef void (*EntityCallback)(void);

typedef struct FieldState {
    u8 pad_0000[0x27b5];
    s8 savedMode;
} FieldState;

typedef struct Entity {
    u8 pad_000[0x1e0];
    EntityCallback shutdownCallback;
    u8 pad_1e4[0x1e8 - 0x1e4];
    EntityCallback drawCallback;
    u8 pad_1ec[0x1f8 - 0x1ec];
    EntityCallback updateCallback;
    u8 pad_1fc[0x20c - 0x1fc];
    EntityCallback modeCallback;
    u8 pad_210[0x218 - 0x210];
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
    EntityCallback thinkCallback;
    u8 pad_10f4[0x10fc - 0x10f4];
    EntityCallback handleCallback;
    u8 pad_1100[0x125c - 0x1100];
    s32 unk_125c;
    s32 unk_1260;
    s32 soloSelection;
    s32 pairSelection;
    s32 savedMode;
    s32 hasSavedMode;
} Entity;

extern FieldState *data_ov001_020a0480;
extern u8 data_020608c8;
extern u8 *GetOverlaySelectionRecord(u32 index);
extern void LoadSceneModelResources(void);
extern void InstallActorCallbacks(Entity *entity);
extern void ShutdownOverlay054(void);
extern void RequestOverlay054ActorState(void);
extern void func_ov054_020d24fc(void);
extern void LoadMenuSoundArcs(void);
extern void func_ov054_020d250c(void);
extern void LoadOverlay054EntityResources(void);
extern void RefreshModeMenuHighlights(void);
extern void func_ov054_020d2794(void);
extern void HandleOverlay054MenuCommand(void);

void InitOverlay054Entity(Entity *entity, int kind)
{
    int i;
    int mode;

    entity->unk_125c = 0;
    entity->unk_1260 = 0;
    mode = data_ov001_020a0480->savedMode;
    entity->savedMode = mode;
    entity->hasSavedMode = 1;
    if (mode == 0) {
        entity->savedMode = 4;
        entity->hasSavedMode = 0;
    }
    entity->soloSelection = -1;
    entity->pairSelection = -1;
    for (i = 1; i < data_020608c8; i++) {
        if (*GetOverlaySelectionRecord(i) != 2) {
            entity->soloSelection = i;
        } else {
            entity->pairSelection = i;
        }
    }
    LoadSceneModelResources();
    entity->kind = kind;
    entity->unk_9b8 = 0;
    entity->stateFlags = 0;
    for (i = 0; i < 4; i++) {
        entity->targets[i] = -1;
    }
    entity->targets[1] = -2;
    InstallActorCallbacks(entity);
    entity->shutdownCallback = ShutdownOverlay054;
    entity->updateCallback = RequestOverlay054ActorState;
    entity->drawCallback = func_ov054_020d24fc;
    entity->stepCallback = LoadMenuSoundArcs;
    entity->modeCallback = func_ov054_020d250c;
    entity->actionCallback = LoadOverlay054EntityResources;
    entity->thinkCallback = RefreshModeMenuHighlights;
    entity->specialCallback = func_ov054_020d2794;
    entity->handleCallback = HandleOverlay054MenuCommand;
}
>>>>>>> 6429ce2ea7ff13b674e183a6843387d9844d00d4
