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

extern OverlayGlobals gFieldSceneGlobals;
extern char gBattleGaugeTaskDescriptor[];
extern char OVERLAY_45_ID[];
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern void SetupFieldBgLayers(void);
extern void SetFieldVisiblePlanes(void);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void *CreateTaskObject(void *descriptor, void *userData);

void OpenOverlayWidgets(void)
{
    OverlayState *state = gFieldSceneGlobals.state;
    TaskParams params;

    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_45_ID);
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
        state->handle = CreateTaskObject(gBattleGaugeTaskDescriptor, &params);
    }
}
