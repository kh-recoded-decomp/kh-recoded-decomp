#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TextWindow {
    u8 pad_00[0x2c];
    u16 tileOffset;
    u16 width;
    u16 height;
    u8 pad_32;
    u8 bgLayer;
} TextWindow;

typedef struct Scene {
    u8 pad_000[0x1fc];
    TextWindow choiceWindow;
    void *choiceLines[4];
    s32 highlightDrawn;
    s32 highlightX;
    s32 highlightY;
    u32 highlightTime;
    u8 pad_250[0x40c - 0x250];
    u64 popupTick;
    u8 pad_414[0x4d0 - 0x414];
    u64 captionTick;
} Scene;

typedef struct SceneGlobals {
    u32 unk_00;
    Scene *scene;
} SceneGlobals;

typedef struct BalloonTailTiles {
    u16 tiles[4][3][2];
} BalloonTailTiles;

extern SceneGlobals data_ov001_020a04a4;
extern const BalloonTailTiles data_ov001_0209dd94;

extern void *func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);
extern void func_ov027_020b9e00(void *widgets, int layer);
extern void ClearChoiceHighlight_020701a8(Scene *scene);
extern void ProjectWorldToScreenFacing_0206fc54(const VecFx32 *world, int *x, int *y);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern void Text_UploadTileBuffer_02001520(void *window);
extern void FillBackgroundLayerRect_02001a60(void *window, u16 *dst, u16 x, u16 y, u8 palette);
extern u32 func_01ff80d4(void);

void ShowChoiceBalloonAtWorldPos_020725dc(const VecFx32 *worldPos, int lineIndex)
{
    int col;
    int row;
    int top;
    int left;
    int x;
    int y;
    int style;
    BOOL offscreen;
    u16 (*shape)[2];
    Scene *scene;
    BalloonTailTiles tail;
    u16 *tilemap;
    TextWindow *window;

    scene = data_ov001_020a04a4.scene;
    window = &scene->choiceWindow;
    tilemap = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    tail = data_ov001_0209dd94;
    offscreen = FALSE;

    if (scene->popupTick != 0 || scene->captionTick != 0) {
        return;
    }
    if (scene->highlightDrawn != 0) {
        ClearChoiceHighlight_020701a8(scene);
    }
    ProjectWorldToScreenFacing_0206fc54(worldPos, &x, &y);
    if (x < 0 || x > 0xff || y < 0 || y > 0xbf) {
        offscreen = TRUE;
    }
    x = (x + 4) / 8;
    y = (y + 4) / 8;
    x = (x > 0x1f) ? 0x1f : (x < 0) ? 0 : x;
    left = x - ((u32)window->width >> 1) + 1;
    left = (left > 0x1f - window->width) ? 0x1f - window->width : (left < 1) ? 1 : left;
    if (y < 6) {
        y = (y > 9) ? 9 : (y < 0) ? 0 : y;
        top = y + 3;
        scene->highlightY = y;
        if (x < 0x10) {
            style = 1;
        } else {
            style = 0;
        }
    } else {
        y = (y - 2 > 9) ? 9 : (y - 2 < 0) ? 0 : y - 2;
        top = y - 2;
        scene->highlightY = top - 2;
        if (x < 0x10) {
            style = 2;
        } else {
            style = 3;
        }
    }
    scene->highlightX = (u32)left - 1;
    SelectListNodeOrFirst_020019b8(window, scene->choiceLines[lineIndex]);
    Text_UploadTileBuffer_02001520(window);
    FillBackgroundLayerRect_02001a60(window, tilemap, left, top, 0xf);
    *(tilemap + (top - 1) * 32 + (left - 1)) = 0xf120;
    *(tilemap + (top - 1) * 32 + (left + window->width)) = 0xf122;
    *(tilemap + (top + window->height) * 32 + (left - 1)) = 0xf126;
    *(tilemap + (top + window->height) * 32 + (left + window->width)) = 0xf128;
    for (row = 0; row < 2; row++) {
        *(tilemap + (top + row) * 32 + (left - 1)) = 0xf123;
        *(tilemap + (top + row) * 32 + (left + window->width)) = 0xf125;
    }
    for (col = 0; col < window->width; col++) {
        *(tilemap + (top - 1) * 32 + (left + col)) = 0xf121;
        *(tilemap + (top + window->height) * 32 + (left + col)) = 0xf127;
    }
    /* Tail tiles point toward the speaker */
    if (!offscreen) {
        int tailCol;
        u16 *tailTiles;
        int tailRow;

        x = (x > 0x1d) ? 0x1d : (x < 1) ? 1 : x;
        for (tailRow = 0, shape = tail.tiles[style]; tailRow < 3; tailRow++) {
            for (tailCol = 0, tailTiles = shape[tailRow]; tailCol < 2; tailCol++) {
                *(tilemap + (tailRow + y) * 32 + (tailCol + x)) = tailTiles[tailCol] | 0xf000;
            }
        }
    }
    func_ov027_020b9e00(func_ov001_0207123c(), 0xb);
    scene->highlightDrawn = 1;
    scene->highlightTime = func_01ff80d4();
}
