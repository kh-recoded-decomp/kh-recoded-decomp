#include "nitro/types.h"

typedef struct OverlayState {
    u8 pad[0x42c];
    void *handle;
    u8 pad430[0x18];
    void *bg3Char;
    void *bg2Char;
    u8 pad450[0xc];
    void *palette;
    u8 pad460[0x20];
    u32 released : 1;
    u32 unk480 : 31;
} OverlayState;

typedef struct OverlayGlobals {
    u32 unk0;
    OverlayState *state;
} OverlayGlobals;

typedef struct TaskParams {
    u16 mode;
    u8 pad[0xe];
} TaskParams;

extern OverlayGlobals data_ov001_020a04c4;
extern char data_ov045_020c0820[];
extern char OVERLAY_45_ID[];
extern void func_02029f8c(int processor, int overlayId);
extern void SetupFieldBgLayers(void);
extern void SetFieldVisiblePlanes(void);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void *func_0202a45c(void *descriptor, void *userData);

void OpenOverlayWidgets(void)
{
    OverlayState *state = data_ov001_020a04c4.state;
    TaskParams params;

    func_02029f8c(0, (int)OVERLAY_45_ID);
    params.mode = 2;
    if (state->handle == NULL) {
        state->released = 0;
        SetupFieldBgLayers();
        SetFieldVisiblePlanes();
        if (state->bg3Char != NULL) {
            GX_LoadBG3Char(state->bg3Char, 0, 0x5800);
            GX_LoadBG2Char(state->bg2Char, 0, 0x1000);
        }
        if (state->palette != NULL) {
            GX_LoadBGPltt(state->palette, 0, 0x200);
        }
        state->handle = func_0202a45c(data_ov045_020c0820, &params);
    }
}
