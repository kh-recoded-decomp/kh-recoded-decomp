#include "src/overlays/ov001/FieldTextFormats.h"

typedef struct PanelHeaderState {
    u8 reserved00[0x18];
    u16 *headerText;
} PanelHeaderState;

typedef char PanelHeaderTextOffsetCheck[
    (u32)&((PanelHeaderState *)0)->headerText == 0x18 ? 1 : -1];

extern PanelHeaderState *data_ov001_020a04e8;
extern s32 GetLanguageIndex(void);
extern s32 func_ov001_02068084(void);
extern s32 func_ov001_02067ed4(void);
extern s32 OS_SNPrintf_0202e094(u16 *out, u32 length, const u16 *format, ...);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 Utf16Length(const u16 *text);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern BOOL func_ov001_0207a8fc(PanelHeaderState *panel);
extern void DrawCacheHeaderText(const u16 *text);

static inline BOOL HasHeaderCharacter(const u16 *text)
{
    return *text != 0;
}

void SetPanelHeaderText(const u16 *prefix, const u16 *name)
{
    PanelHeaderState *panel = data_ov001_020a04e8;
    BOOL showPrefix = TRUE;
    const u16 *separator;
    s32 mode, panelId;
    u16 buffer[0x40];
    u16 *source, *destination;
    u16 character;

    separator = GetLanguageIndex() == 2 ? gFieldTextFormats.spacedColon : gFieldTextFormats.colonSpace;
    mode = func_ov001_02068084();
    panelId = func_ov001_02067ed4();
    if (mode == 0) {
        switch (panelId) {
        case 1:
        case 2:
        case 3:
            showPrefix = FALSE;
            break;
        }
    } else if ((GetLanguageIndex() == 5 || GetLanguageIndex() == 4) && mode == 2) {
        switch (panelId) {
        case 10:
        case 11:
        case 12:
            showPrefix = FALSE;
            break;
        }
    }
    if (prefix == NULL || !showPrefix) {
        OS_SNPrintf_0202e094(buffer, 0x40, gFieldTextFormats.copyString, name);
    } else {
        OS_SNPrintf_0202e094(buffer, 0x40, gFieldTextFormats.joinThreeStrings, prefix, separator, name);
    }
    if (panel->headerText != NULL) {
        NNSi_FndFreeFromDefaultHeap(panel->headerText);
    }
    panel->headerText = NNSi_FndAllocFromDefaultHeap((Utf16Length(buffer) + 1) * sizeof(u16));
    source = buffer;
    destination = panel->headerText;
    character = *source;
    if (HasHeaderCharacter(source)) {
        do {
            if (character != '\n') {
                *destination++ = character;
            }
            character = *++source;
        } while (character != 0);
    }
    *destination = 0;
    if (func_ov001_0207a8fc(panel)) {
        DrawCacheHeaderText(panel->headerText);
    }
}
