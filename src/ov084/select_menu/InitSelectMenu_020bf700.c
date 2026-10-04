#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 rest[4];
} TextFrame;

typedef struct ButtonTemplate {
    u16 id;
    s16 x;
    s16 y;
    u8 pad6[0xa];
    int userData;
} ButtonTemplate;

typedef struct ModelOffset {
    int x;
    int y;
    int z;
} ModelOffset;

typedef struct SelectMenu {
    u8 selection;
    u8 enabledMask;
    u8 dirty;
    u8 pad3;
    TextLayer titleLayer;
    TextLayer optionLayer;
    TextLayer helpLayer;
    const u16 *optionText[2];
    const u16 *helpText[2];
    void *records;
    void *buttons[2];
    void *cursor;
    void *marker;
    u8 strings[0xc];
    u8 model[0xa4];
    ModelOffset modelOffset;
    u8 pad180[0x28];
    u8 blendTable[4];
} SelectMenu;

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG0CNT  (*(vu16 *)0x04000008)
#define REG_BG1CNT  (*(vu16 *)0x0400000a)
#define REG_BG2CNT  (*(vu16 *)0x0400000c)
#define REG_BG3CNT  (*(vu16 *)0x0400000e)
#define REG_POWCNT  (*(vu16 *)0x04000304)

extern TextFrame data_ov084_020bfc40;
extern char data_ov084_020bfcc4[];
extern void *data_0205fe0c;
extern ModelOffset data_02053438;

extern void func_ov039_020be6a0(void);
extern void SetSelectionIfChanged_020bc92c(int id);
extern u8 func_ov039_020bc828(void);
extern void func_ov039_020bc914(void);
extern void OpenTextFrame_020be5b8(u32 position, u32 size, int layer, TextLayer *text, TextFrame *frame);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern const u16 *func_ov027_020ba2a8(void *strings, int index);
extern const u16 *func_ov039_020bcb20(void *state);
extern BOOL SetTextColorIfFits_020bcd04(TextLayer *layer, int limit, const u16 *text);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);
extern void *func_ov039_020bc18c(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void func_ov027_020b7e24(void *records, u32 imageParams);
extern ButtonTemplate *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void *AddRecordFromTemplate_020b7ecc(void *pool, ButtonTemplate *source, u16 id, int userData);
extern void func_ov027_020b81e8(void *pool, void *record, int x, int y);
extern void *FindLoadedElementById_020b8390(void *pool, u32 id);
extern void apply_all_pending_entry_edits_020b84f4(void *pool, void *cursor, int x, int y);
extern void SetTagRecordArmed_020b83e8(void *pool, void *record, BOOL arm);
extern void func_ov039_020bc318(int a, int b, int c, int d, int e, int f);
extern void func_ov039_020bc414(int a, int b, int c);
extern u32 func_ov039_020bc7f8(void);
extern u32 ObjectManager_GetFirstEntryParam_0207ee14(int index);
extern u32 ObjectManager_GetSecondEntryParam_0207ee48(int index);
extern void *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, int mode);
extern void *func_0202c48c(u32 fileId, int mode);
extern void func_0202ed9c(void *object, void *model, void *animation, int heap);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void selectJointAnimationBlend_0202f2cc(void *state, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void PrepareAndStartStream_0204dd4c(int channel, int stream);
extern void func_ov039_020bc7e0(int value);

BOOL InitSelectMenu_020bf700(SelectMenu *menu)
{
    TextFrame frame;
    void *records;
    ButtonTemplate *template;
    const u16 *text;
    void *modelFile;
    void *animFile;
    int modelId;
    s16 stringIndex;
    s16 i;
    int button;

    func_ov039_020be6a0();
    REG_POWCNT |= 0x8000;
    REG_BG0CNT = (u16)((REG_BG0CNT & ~3) | 1);
    REG_BG1CNT = (u16)(REG_BG1CNT & ~3);
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 2);
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 3);
    REG_BG2CNT = (u16)((REG_BG2CNT & 0x43) | (0x1e << 8));
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (0xf << 8);
    SetSelectionIfChanged_020bc92c(5);
    menu->selection = func_ov039_020bc828();
    menu->enabledMask = 3;
    frame = data_ov084_020bfc40;
    func_ov039_020bc914();
    OpenTextFrame_020be5b8(0x8, 0x20018, 1, &menu->titleLayer, &frame);
    OpenTextFrame_020be5b8(0x30002, 0x10001c, 1, &menu->optionLayer, &frame);
    OpenTextFrame_020be5b8(0x150000, 0x30020, 1, &menu->helpLayer, &frame);

    stringIndex = 0;
    LoadPackedFileView_020ba25c(menu->strings, data_ov084_020bfcc4, FALSE);
    for (i = 0; i < 2; i++) {
        menu->optionText[i] = func_ov027_020ba2a8(menu->strings, stringIndex++);
        menu->helpText[i] = func_ov027_020ba2a8(menu->strings, stringIndex++);
    }
    text = func_ov039_020bcb20(data_0205fe0c);
    SetTextColorIfFits_020bcd04(&menu->titleLayer, 0xac, text);
    DrawTextAnchored_020015a0(&menu->titleLayer, 0xbe, 2, 2, 0x20, text);

    records = func_ov039_020bc18c();
    func_ov027_020b7e24(records, BuildSlotImageParams_020bc220(2, 4));
    template = FindActiveRecordById_020b8184(records, 5);
    for (button = 0; button < 2; button++) {
        menu->buttons[button] = AddRecordFromTemplate_020b7ecc(records, template, button + 8, template->userData);
        func_ov027_020b81e8(records, menu->buttons[button], template->x, (s16)(template->y + button * 3));
    }
    menu->cursor = FindLoadedElementById_020b8390(records, 0);
    menu->marker = FindActiveRecordById_020b8184(records, 7);
    apply_all_pending_entry_edits_020b84f4(records, menu->cursor, template->x, template->y);
    SetTagRecordArmed_020b83e8(records, menu->cursor, TRUE);
    func_ov039_020bc318(2, 1, 1, 4, 3, 0);
    func_ov039_020bc414(3, 0, 0x60);
    menu->records = records;

    if (func_ov039_020bc7f8() & 0x8000) {
        modelId = 0x2e;
    } else {
        modelId = 0x22;
    }
    modelFile = RetainOrInitializeSharedRecord_0202c80c(ObjectManager_GetFirstEntryParam_0207ee14(modelId), 0xe);
    animFile = func_0202c48c(ObjectManager_GetSecondEntryParam_0207ee48(modelId), 0xe);
    func_0202ed9c(menu->model, modelFile, animFile, 0xe);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(animFile);
    menu->modelOffset = data_02053438;
    selectJointAnimationBlend_0202f2cc(menu->model, 0, menu->blendTable, 0);
    if ((func_ov039_020bc7f8() & 0x8001) == 0) {
        PrepareAndStartStream_0204dd4c(0, 0xb);
        func_ov039_020bc7e0(1);
    }
    menu->dirty = 2;
    return TRUE;
}
