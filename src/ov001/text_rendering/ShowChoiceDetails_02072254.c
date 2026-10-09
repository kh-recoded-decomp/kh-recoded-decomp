#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct LabelSet {
    const u16 *labels[3];
} LabelSet;

typedef struct ColorSet {
    int colors[3];
} ColorSet;

typedef struct ChoiceEntry {
    u16 nameIndex;
    u8 count;
    u8 rank;
} ChoiceEntry;

typedef struct ChoiceScene {
    u8 pad_000[0x1c];
    u8 tracker[0x5c];
    u8 boxNormal[0xc];
    u8 boxWide[0x108];
    u8 textLayer[0x280];
    u32 shownTick[2];
    u8 pad_414[0xf8];
    u8 formatter[0x628];
    const u16 *names[1];
} ChoiceScene;

typedef struct ChoiceGlobals {
    u32 unk_00;
    ChoiceScene *scene;
} ChoiceGlobals;

extern ChoiceGlobals data_ov001_020a04a4;
extern LabelSet data_ov001_0209ecb4;
extern ColorSet data_ov001_0209dbe8;
extern LabelSet data_ov001_0209ec9c;
extern LabelSet data_ov001_0209ec90;
extern LabelSet data_ov001_0209eca8;

extern void *GetPanelLayerScreen_0206ea08(s32 layer);
extern BOOL IsMenuSlotBusy_02078910(void);
extern void PlaySoundChecked_0204d8d0(void *ptr, int arg);
extern void ClearChoiceHighlight_020701a8(ChoiceScene *scene);
extern u64 OS_GetTick_02003fd4(void);
extern void *FindActiveRecordById_020b8184(void *tracker, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern int func_02001908(void *layer, const u16 *text, int flags);
extern void Obj_SetField14_02001490(void *layer, void *box);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern int func_0202b788(void);
extern int func_ov027_020ba2e0(void *formatter, u32 id, u16 *buffer, u32 size, ...);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern void *UpdateWidgetLayerDefault_020b9df0(ChoiceScene *scene, int layer);
extern void FillBackgroundLayerRect_02001a60(void *layer, void *dst, int x, int y, u8 palette);
extern void MarkTileTableRowDirty_020b9e00(ChoiceScene *scene, int id);

static inline void DrawName(ChoiceScene *scene, u16 index)
{
    DrawTextAnchored_020015a0(scene->textLayer, 0, 0, 2, 0x209, scene->names[index]);
}

void ShowChoiceDetails_02072254(ChoiceEntry *entry, BOOL confirm)
{
    ChoiceScene *scene = data_ov001_020a04a4.scene;
    int width;
    void *screen;
    u16 buffer[0x20];
    LabelSet defaultLabels;
    ColorSet colors;
    LabelSet labelsB;
    LabelSet labelsC;
    LabelSet labelsD;
    const u16 *label;

    screen = GetPanelLayerScreen_0206ea08(0xb);
    defaultLabels = data_ov001_0209ecb4;
    colors = data_ov001_0209dbe8;
    labelsB = data_ov001_0209ec9c;
    labelsC = data_ov001_0209ec90;
    labelsD = data_ov001_0209eca8;
    if (IsMenuSlotBusy_02078910()) {
        if (confirm) {
            PlaySoundChecked_0204d8d0(NULL, 9);
            return;
        }
        PlaySoundChecked_0204d8d0(NULL, 4);
        return;
    }
    ClearChoiceHighlight_020701a8(scene);
    *(u64 *)scene->shownTick = OS_GetTick_02003fd4();
    TagTracker_InvokeCallback_020b8210(scene->tracker,
                                       FindActiveRecordById_020b8184(scene->tracker, confirm ? 0x34 : 0x36));
    CallVirtualHandlerSlot1_02001574(scene->textLayer, 1);
    if (func_02001908(scene->textLayer, scene->names[entry->nameIndex], 0) >= 0x32) {
        Obj_SetField14_02001490(scene->textLayer, scene->boxWide);
    }
    DrawName(scene, entry->nameIndex);
    width = func_02001908(scene->textLayer, scene->names[entry->nameIndex], 0);
    if (entry->rank >= 1) {
        switch (func_0202b788()) {
        case 2:
            label = labelsB.labels[entry->rank - 1];
            break;
        case 3:
            label = labelsC.labels[entry->rank - 1];
            break;
        case 5:
            label = labelsD.labels[entry->rank - 1];
            break;
        default:
            label = defaultLabels.labels[entry->rank - 1];
            break;
        }
        DrawTextAnchored_020015a0(scene->textLayer, width, 0, colors.colors[entry->rank - 1], 0x209, label);
        width += func_02001908(scene->textLayer, label, 0);
    }
    if (entry->count >= 1) {
        func_ov027_020ba2e0(scene->formatter, 4, buffer, 0x20, entry->count);
        DrawTextAnchored_020015a0(scene->textLayer, width + 2, 0, 2, 0x209, buffer);
    }
    FlushBufferAndRunCallback_0200153c(scene->textLayer);
    Obj_SetField14_02001490(scene->textLayer, scene->boxNormal);
    if (screen == NULL) {
        FillBackgroundLayerRect_02001a60(scene->textLayer, UpdateWidgetLayerDefault_020b9df0(scene, 0xb), 1, 7, 0xf);
        MarkTileTableRowDirty_020b9e00(scene, 0xb);
    } else {
        FillBackgroundLayerRect_02001a60(scene->textLayer, screen, 1, 7, 0xf);
    }
    if (confirm) {
        PlaySoundChecked_0204d8d0(NULL, 9);
        return;
    }
    PlaySoundChecked_0204d8d0(NULL, 4);
}
