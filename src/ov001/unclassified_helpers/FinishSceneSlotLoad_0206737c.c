#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneResourceEntry {
    u8 kind;
} SceneResourceEntry;

typedef struct SceneBlendTable {
    s16 trackCounts[5];
} SceneBlendTable;

typedef struct SceneSlot {
    u8 pad_00[0xa4];
    VecFx32 translation;
    u8 pad_B0[0x28];
    SceneBlendTable blendTable;
    u8 pad_E2[0x22];
    u8 flags;
    u8 kind;
    s8 blendIndex;
    u8 pad_107;
} SceneSlot;

typedef struct SceneContext {
    u8 pad_00[0x18];
    SceneSlot slots[16];
} SceneContext;

typedef struct SceneLoadRequest {
    u8 active;
    s8 slotIndex;
    u8 pad_02[2];
    void *primaryRecord;
    void *secondaryFile;
    SceneResourceEntry *entry;
} SceneLoadRequest;

extern void func_0202ed80(SceneSlot *object, void *record, s32 sourceB, void *extra);
extern void func_0202ed9c(SceneSlot *object, void *record, void *sourceA, void *extra);
extern void BlendToAnimationTrack_0202f374(SceneSlot *state, u16 trackIndex, SceneBlendTable *table, s16 blendIndex, int frameCount);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

BOOL FinishSceneSlotLoad_0206737c(SceneLoadRequest *request, SceneContext *ctx) {
    VecFx32 zero = {0, 0, 0};
    void *record = request->primaryRecord;

    if (record != NULL) {
        s32 i;
        SceneSlot *slot = &ctx->slots[request->slotIndex];

        if (request->secondaryFile != NULL) {
            func_0202ed9c(slot, record, request->secondaryFile, NULL);
        } else {
            func_0202ed80(slot, record, 1, NULL);
        }
        slot->kind = request->entry->kind;
        slot->translation = zero;
        for (i = 0; i < 5; i++) {
            u16 track = i;
            if (slot->blendTable.trackCounts[track] > 0) {
                BlendToAnimationTrack_0202f374(slot, track, &slot->blendTable, slot->blendIndex, 0);
            }
        }
        slot->flags |= 0x80;
        request->primaryRecord = NULL;
        if (request->secondaryFile != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(request->secondaryFile);
            request->secondaryFile = NULL;
        }
        request->entry = NULL;
        request->active = 0;
        return FALSE;
    }
    return TRUE;
}
