#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} FieldContext;

extern FieldContext *data_ov028_020bb3a0;
extern BOOL Panel_TryBeginTransition4(void);
extern void SuspendTaskAndSetFlag(void);
extern void SetMenuHighlight(s32 enable);
extern s32 func_ov001_0206dc38(void);
extern void ReleaseActorSlotByIndex(s32 index);
extern VecFx32 *func_ov001_0206dc4c(s32 index);
extern u16 GetBiasAdjustedField(s32 index);
extern void StoreSessionSpawnPoint(s32 index, VecFx32 *position, u16 angle);
extern void func_ov001_020685d4(void);
extern void SetOverlayLayerVisible(s32 value);
extern void func_ov001_0207efa0(void);
extern void ShutdownSceneContext(void);
extern void func_ov001_0207d680(void);
extern void func_ov001_02064d88(void);
extern void PopVramState(void);
extern void ActorRegistry_ClearCollisionResult(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern void StoreToGlobalPtr4Field28(int value);

s32 ShutdownFieldAndSaveActorPoses(void)
{
    s32 index;
    VecFx32 *position;

    if ((data_ov028_020bb3a0->flags & 0x10) == 0 && !Panel_TryBeginTransition4()) {
        return -1;
    }
    SuspendTaskAndSetFlag();
    SetMenuHighlight(1);
    for (index = 0; index < func_ov001_0206dc38(); index++) {
        ReleaseActorSlotByIndex(index);
        position = func_ov001_0206dc4c(index);
        StoreSessionSpawnPoint(index, position, GetBiasAdjustedField(index));
    }
    func_ov001_020685d4();
    SetOverlayLayerVisible(1);
    func_ov001_0207efa0();
    ShutdownSceneContext();
    data_ov028_020bb3a0->flags &= ~0xC;
    func_ov001_0207d680();
    func_ov001_02064d88();
    PopVramState();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    data_ov028_020bb3a0->flags |= 0x8000;
    return 0x12;
}
