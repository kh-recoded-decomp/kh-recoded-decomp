#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touching;
    u16 invalid;
} TouchSample;

typedef struct MapMenuState {
    u8 pad_00[0x10];
    void *screenData;
    u8 pad_14[0x10];
    BOOL screenPending;
    BOOL screenLoaded;
    BOOL dirty;
    u8 pad_30[0x4];
    BOOL cursorReset;
    BOOL menuShown;
    BOOL routeOpen;
    u8 pad_40[0x18];
    u8 renderer[0x6434];
    s32 markerSlot;
    u8 pad_6490[0x10];
    s32 menuSlot;
    u8 pad_64A4[0x1b08];
    TouchSample lastTouch;
    u8 pad_7FB4[0x8];
    u16 screenWidth;
    u16 screenHeight;
} MapMenuState;

extern MapMenuState *data_ov023_020b6f64;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern s32 func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void func_ov023_020b5c64(MapMenuState *state, VecFx32 *pos);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void SetEntryRotation_0204f308(void *renderer, int slot, int rotation);
extern BOOL IsFieldFlag13OrSessionFlagSet_020728e4(void);
extern void PlaceMapStoryIcons_020b653c(MapMenuState *state);
extern void func_ov023_020b65ac(MapMenuState *state);
extern void ResetMapMenuCursor_020b69bc(MapMenuState *state);
extern BOOL CanOpenFieldMenu_020735d8(void);
extern BOOL func_ov001_0207b5f4(void);
extern void func_0204f378(void *renderer, int slot, int value);
extern void *CopySourceBlock_020b9f7c(TouchSample *out);
extern void func_ov001_0207b6b4(void);
extern void func_ov001_0207b320(int mode);
extern void PlaySoundEffect_0204d924(int channel, int sound);
extern void func_ov001_0207b6c4(void);
extern void func_01ff89a8(const void *src, void *dest, u32 size);

void *UpdateMapMenuState_020b6afc(void)
{
    MapMenuState *state = data_ov023_020b6f64;
    TouchSample touch;

    if (state->screenLoaded && state->screenPending) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state->screenData);
        state->screenData = NULL;
        state->screenPending = FALSE;
        state->screenLoaded = FALSE;
    }
    if (state->screenWidth != 0 && state->screenHeight != 0) {
        if (func_ov001_0206dc38() > 0) {
            func_ov023_020b5c64(state, func_ov001_0206dc4c(0));
            SetEntryRotation_0204f308(state->renderer, state->markerSlot, GetBiasAdjustedField_0206dc80(0));
        }
        if (IsFieldFlag13OrSessionFlagSet_020728e4()) {
            PlaceMapStoryIcons_020b653c(state);
        }
        func_ov023_020b65ac(state);
    }
    if (state->cursorReset) {
        ResetMapMenuCursor_020b69bc(state);
    }
    if (state->routeOpen) {
        if (!state->menuShown && CanOpenFieldMenu_020735d8() && func_ov001_0207b5f4()) {
            func_0204f378(state->renderer, state->menuSlot, 1);
            state->menuShown = TRUE;
        } else if ((state->menuShown && !CanOpenFieldMenu_020735d8()) || !func_ov001_0207b5f4()) {
            func_0204f378(state->renderer, state->menuSlot, 0);
            state->menuShown = FALSE;
        }
    }
    CopySourceBlock_020b9f7c(&touch);
    if (state->menuShown) {
        if (touch.touching == 1) {
            if (state->lastTouch.touching == 0 && touch.invalid == 0 && touch.x >= 0xc0 && touch.x <= 0xff
                && touch.y >= 0x86 && touch.y <= 0xa6) {
                func_ov001_0207b6b4();
                func_ov001_0207b320(2);
                PlaySoundEffect_0204d924(0, 0x3b);
            }
        } else {
            func_ov001_0207b6c4();
        }
    }
    func_01ff89a8(&touch, &state->lastTouch, sizeof(TouchSample));
    state->dirty = TRUE;
    return NULL;
}
