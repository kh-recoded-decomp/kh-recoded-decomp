#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x34];
    u8 textLayer[0x34];
    s32 mode;
    u8 pad_06C[0x8];
    void *modeLabels[0x24];
    void *menuLabel;
    u8 pad_108[0x20];
    s32 shown;
    s32 dirty;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *GetSceneTagTracker_020711b0(void);
extern void *func_ov001_0207123c(void);
extern u16 *UpdateFieldWidgetLayer_020736b4(int layerId);
extern void func_ov001_02078360(int a, int b);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void func_ov001_02075e10(FieldMenu *menu, void *pool, void *label);
extern void SelectListNodeOrFirst_020019b8(void *list, void *node);
extern void Text_UploadTileBuffer_02001520(void *text);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern void func_ov001_02078ac4(void);
extern BOOL HasFieldOverlayScreen_02073698(void);
extern void func_ov001_02076ebc(FieldMenu *menu, int arg);
extern void func_ov001_020769f4(FieldMenu *menu);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void func_ov027_020b9e00(void *layers, int layerId);

void SetFieldMenuMode_020781a4(int mode) {
    FieldMenu *menu = data_ov001_020a04b0.menu;
    void *pool = GetSceneTagTracker_020711b0();
    void *layers = func_ov001_0207123c();
    u16 *dst = UpdateFieldWidgetLayer_020736b4(0xb);
    BOOL refresh = FALSE;
    BOOL shown;

    switch (mode) {
    case -1:
        shown = FALSE;
        func_ov001_02078ac4();
        break;
    case 10:
        shown = TRUE;
        func_ov001_02078360(0, 1);
        TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 0x24));
        func_ov001_02075e10(menu, pool, menu->menuLabel);
        InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0xc));
        InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x55));
        SelectListNodeOrFirst_020019b8(menu->textLayer, menu->modeLabels[mode]);
        Text_UploadTileBuffer_02001520(menu->textLayer);
        refresh = TRUE;
        break;
    default:
        if (menu->mode == 10) {
            TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, (u16)(IsFieldFlag8Set_020728a4() ? 0xe : 0xc)));
            TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 0x21));
            func_ov001_02075e10(menu, pool, menu->menuLabel);
            refresh = TRUE;
        }
        shown = TRUE;
        SelectListNodeOrFirst_020019b8(menu->textLayer, menu->modeLabels[mode]);
        Text_UploadTileBuffer_02001520(menu->textLayer);
        func_ov001_02078ac4();
        break;
    }

    menu->mode = mode;
    menu->dirty = 1;
    if (!HasFieldOverlayScreen_02073698()) {
        func_ov001_02076ebc(menu, 0);
    }
    if (refresh) {
        func_ov001_020769f4(menu);
    }
    if ((shown && !menu->shown) || (!shown && menu->shown)) {
        FillBackgroundLayerRect_02001a60(menu->textLayer, dst, 2, 0x16, 10);
        func_ov027_020b9e00(layers, 0xb);
        menu->shown = shown;
    }
}
