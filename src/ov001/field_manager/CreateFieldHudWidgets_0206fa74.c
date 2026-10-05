#include "nitro/types.h"

typedef void (*HudCallback)(void);

typedef struct HudResource {
    u8 pad_00[0xc];
    u32 value0C;
    u32 value10;
    u32 value14;
} HudResource;

typedef struct HudSetup {
    u32 unk_00;
    HudResource *gauge;
    HudResource *extra;
} HudSetup;

typedef struct GaugeParams {
    u16 widths[3];
    u16 heights[3];
    u32 resource;
} GaugeParams;

typedef struct FieldHud {
    u8 pad_000[0x414];
    void *gaugeWidget;
    void *portraitWidget;
    void *frameWidget;
    void *timerWidget;
    void *counterWidget;
    void *statusWidget;
    u8 pad_42C[0x4];
    void *extraWidget;
    u8 pad_434[0x4];
    void *overlayWidget;
    u8 pad_43C[0x1cc];
    s32 memberIds[3];
    u8 pad_614[0xd2c];
    HudCallback promptCallbacks[6];
} FieldHud;

extern u8 data_ov027_020ba394[];
extern u8 data_ov027_020ba380[];
extern u8 data_ov001_0209ee2c[];
extern u8 data_ov001_0209ee9c[];
extern u8 data_ov001_0209eef0[];
extern u8 data_ov001_0209ef38[];
extern u8 data_ov001_0209ef94[];
extern u8 data_ov001_0209eff0[];

extern u8 *GetOverlaySelectionRecord(int index);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_01ff8830(void *dst, int val, u32 size);
extern unsigned int MakePrimaryVramKey_020711ec(unsigned int slot);
extern void *func_0202c48c(unsigned int fileId, int heapId);
extern void func_02014d38(void *file, HudResource **out);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void OpenArrowPrompt_0207dd14(void);
extern void func_ov001_0207de48(void);
extern void ArrowPrompt_HandleDpad_0207dfe4(void);
extern void func_ov001_0207e094(void);
extern void func_ov001_0207e0a0(void);
extern void func_ov001_0207e0ac(void);

void CreateFieldHudWidgets_0206fa74(FieldHud *hud, HudSetup *setup)
{
    int scene = *(s16 *)(GetOverlaySelectionRecord(0) + 0x130);
    u32 resource;
    HudResource *graphic;
    GaugeParams params;
    void *file;
    int i;

    hud->frameWidget = func_0202a448(data_ov027_020ba394, NULL);
    func_01ff8830(&params, 0, sizeof(GaugeParams));
    params.widths[0] = 0x3c;
    params.heights[0] = 0x3c;
    for (i = 1; i < 3; i++) {
        if (hud->memberIds[i] != -1) {
            params.widths[i] = 0x3c;
            params.heights[i] = 0x3c;
        }
    }
    params.resource = setup->gauge->value14;
    hud->gaugeWidget = func_0202a448(data_ov001_0209ee2c, &params);
    file = func_0202c48c(MakePrimaryVramKey_020711ec(0xc), 0xe);
    func_02014d38(file, &graphic);
    resource = graphic->value14;
    hud->portraitWidget = func_0202a448(data_ov001_0209ee9c, &resource);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    hud->timerWidget = func_0202a448(data_ov001_0209eef0, NULL);
    hud->counterWidget = func_0202a448(data_ov001_0209ef38, NULL);
    hud->statusWidget = func_0202a448(data_ov001_0209ef94, NULL);
    switch (scene) {
    case 0xc4:
        hud->promptCallbacks[0] = OpenArrowPrompt_0207dd14;
        hud->promptCallbacks[1] = func_ov001_0207de48;
        hud->promptCallbacks[2] = ArrowPrompt_HandleDpad_0207dfe4;
        hud->promptCallbacks[3] = func_ov001_0207e094;
        hud->promptCallbacks[4] = func_ov001_0207e0a0;
        hud->promptCallbacks[5] = func_ov001_0207e0ac;
    case 0xc5:
    case 0xc6:
    case 0xca:
        hud->extraWidget = func_0202a448(data_ov001_0209eff0, (void *)setup->extra->value0C);
    default:
        hud->overlayWidget = func_0202a448(data_ov027_020ba380, NULL);
        break;
    }
}
