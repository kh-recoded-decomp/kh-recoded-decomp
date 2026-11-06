#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
} PointPair;

typedef struct {
    u8 pad_00[0x10];
    PointPair current;
    u8 pad_18[0x60];
    PointPair target;
    PointPair previous;
    u8 pad_88[0x4];
    s32 id;
    u8 pad_90[0xC];
} SceneEntry;

typedef struct {
    u8 pad_00[0x4C];
    s32 flag;
} SceneOptions;

typedef struct {
    u8 pad_00[0x8];
    s32 state;
    u8 pad_0C[0xC74];
    s32 busy;
    u8 pad_C84[0x40C];
    SceneEntry *entries;
    u8 pad_1094[0x4];
    SceneOptions *options;
    u8 pad_109C[0x44];
    s32 bgmId;
    s32 bgmFade;
} SceneContext;

typedef struct {
    u8 pad_00[0x4];
    SceneContext *context;
} SceneHolder;

typedef struct {
    u8 pad_00[0x27F8];
    u8 resetFlag;
} GameState;

extern SceneHolder data_ov036_020c3940;
extern GameState *gFieldSessionWork;
extern s32 RunPanelSubScriptFrame(void);
extern int GetScriptBgmSelection(void);
extern int QueueSoundKind4(int id, int fade);
extern u32 SetScriptBgmSelection(u32 value);
extern BOOL IsSessionFlagSet(u32 value);
extern int GetMainBrightnessSetting(void);
extern void G2x_SetBlendAlpha_(unsigned int *reg, unsigned int plane1, unsigned int plane2, unsigned int ev1, unsigned int ev2);
extern void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth, unsigned polygonID, int fog);
extern u32 SetPanelEnabled(u32 value);

s32 AdvancePanelScriptSkipAndRestoreScene(void)
{
    SceneContext *context = data_ov036_020c3940.context;
    s32 bgmId;
    int i;

    context->state = RunPanelSubScriptFrame();
    if (context->busy == 0) {
    if (context->state == -1) {
        context->state = 3;
    }
    bgmId = context->bgmId;
    if (bgmId != GetScriptBgmSelection() && (bgmId == -1 || bgmId > 1)) {
        if (context->bgmFade == 0) {
            context->bgmFade = 20;
        }
        QueueSoundKind4(context->bgmId & 0xFF, context->bgmFade);
        SetScriptBgmSelection(context->bgmId);
    }
    if (!IsSessionFlagSet(0x3308) && GetScriptBgmSelection() == -1) {
        gFieldSessionWork->resetFlag = 0;
    }
    if (GetMainBrightnessSetting() == 0) {
        for (i = 0; i < 8; i++) {
            SceneEntry *entry = &context->entries[i];
            if (entry->id != -1) {
                entry->previous = entry->current;
                entry->current = entry->target;
            }
        }
        context->state = 4;
    } else {
        G2x_SetBlendAlpha_((unsigned int *)0x04000050, 1, 0x22, 0, 0x10);
        if (context->options->flag != 0) {
            G3X_SetClearColor(0x7FFE, 0x1F, 0x7FFF, 0x3F, 0);
        } else {
            G3X_SetClearColor(0, 0, 0x7FFF, 0x3F, 0);
        }
        SetPanelEnabled(1);
    }
    return 1;
    }
    return 0;
}
