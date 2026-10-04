#include "nitro/types.h"

typedef struct ConfigChoice {
    const void *name;
    const void *description;
} ConfigChoice;

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
    const void *label;
    ConfigChoice choices[1];
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[3];
    const void *title;
    ConfigOption *options[6];
} ConfigPage;

typedef struct TagLayout {
    u8 pad_00[2];
    s16 x;
    s16 y;
    u8 pad_06[0xa];
    int userData;
} TagLayout;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 helpShown;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[3];
    void *tracker;
    void *rowTags[6];
    void *cursorTag;
    void *helpTag;
    void *headerTag;
    void *pageTabs[3];
    void *footerTag;
    void *arrowLeft;
    void *arrowRight;
    void *arrowLeftHelp;
    void *arrowRightHelp;
    ConfigPage pages[3];
    u8 objectLists[5][0x34];
    void *image;
    u8 pad_1b8[8];
} ConfigMenu;

typedef struct FrameStyle {
    u16 data[8];
} FrameStyle;

extern const FrameStyle data_ov079_020c4c10;
extern char data_ov079_020c4c84[];
extern void *data_0205fe0c;

extern void func_01ff8830(void *dest, int value, u32 size);
extern void OpenTextFrame_020be5b8(u32 position, u32 size, int layer, void *frame, FrameStyle *style);
extern void LoadPackedFileView_020ba25c(void **out, const void *path, int flags);
extern void *func_ov039_020bcb20(void *save);
extern BOOL SetTextColorIfFits_020bcd04(void *list, int limit, const void *text);
extern void DrawTextAnchored_020015a0(void *list, int x, int y, int color, u32 flags, const void *text);
extern void *func_ov039_020bc18c(void);
extern int BuildSlotImageParams_020bc220(int slot, u32 low);
extern void func_ov027_020b7e24(void *pool, int params);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern ConfigOption *ConfigMenu_CreateOption_020c4718(void *messages, int labelIndex, int count, int spec);
extern void *FindLoadedElementById_020b8390(void *pool, u32 id);
extern TagLayout *FindActiveRecordById_020b8184(void *pool, u32 id);
extern void *AddRecordFromTemplate_020b7ecc(void *pool, TagLayout *source, u16 id, int userData);
extern void func_ov027_020b81e8(void *pool, void *tag, s16 x, s16 y);
extern void SetTagRecordArmed_020b83e8(void *pool, void *tag, BOOL arm);
extern int func_ov039_020bc914(void);
extern void func_ov039_020bc318(int a, int b, int c, int d, int e, u16 f);
extern void func_ov039_020bc414(int a, int b, int c);

BOOL ConfigMenu_Init_020c4260(ConfigMenu *menu)
{
    FrameStyle style;
    void *title;
    void *pool;
    TagLayout *layout;
    u16 y;
    u16 x;
    u16 nextId;
    u16 i;

    func_01ff8830(menu, 0, sizeof(ConfigMenu));
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
    style = data_ov079_020c4c10;
    OpenTextFrame_020be5b8(0x00000008, 0x00020018, 1, menu->objectLists[0], &style);
    OpenTextFrame_020be5b8(0x00030002, 0x0002000d, 1, menu->objectLists[1], &style);
    OpenTextFrame_020be5b8(0x00060004, 0x000c000b, 1, menu->objectLists[2], &style);
    OpenTextFrame_020be5b8(0x00060011, 0x000c000b, 1, menu->objectLists[3], &style);
    OpenTextFrame_020be5b8(0x00150000, 0x00030020, 1, menu->objectLists[4], &style);
    LoadPackedFileView_020ba25c(&menu->image, data_ov079_020c4c84, 0);
    title = func_ov039_020bcb20(data_0205fe0c);
    SetTextColorIfFits_020bcd04(menu->objectLists[0], 0xac, title);
    DrawTextAnchored_020015a0(menu->objectLists[0], 0xbe, 2, 2, 0x20, title);
    menu->dirty = TRUE;
    pool = func_ov039_020bc18c();
    nextId = 0x21;
    func_ov027_020b7e24(pool, BuildSlotImageParams_020bc220(0, 6));

    menu->pages[0].rowCount = 6;
    menu->pages[0].title = func_ov027_020ba2a8(&menu->image, 0);
    menu->pages[0].options[0] = ConfigMenu_CreateOption_020c4718(&menu->image, 1, 2, 0x4005);
    menu->pages[0].options[1] = ConfigMenu_CreateOption_020c4718(&menu->image, 6, 2, 0x4006);
    menu->pages[0].options[2] = ConfigMenu_CreateOption_020c4718(&menu->image, 0xb, 3, 0x8003);
    menu->pages[0].options[3] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x12, 2, 0x4002);
    menu->pages[0].options[4] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x1c, 2, 0x4007);
    menu->pages[0].options[5] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x17, 2, 0x400a);

    menu->pages[1].rowCount = 3;
    menu->pages[1].title = func_ov027_020ba2a8(&menu->image, 0x21);
    menu->pages[1].options[0] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x22, 2, 0x4009);
    menu->pages[1].options[1] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x27, 2, 0x4010);
    menu->pages[1].options[2] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x2c, 3, 0x8012);

    menu->pages[2].rowCount = 5;
    menu->pages[2].title = func_ov027_020ba2a8(&menu->image, 0x33);
    menu->pages[2].options[0] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x34, 2, 0x4011);
    menu->pages[2].options[1] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x39, 2, 0x4014);
    menu->pages[2].options[2] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x3e, 3, 0x800c);
    menu->pages[2].options[3] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x45, 2, 0x4015);
    menu->pages[2].options[4] = ConfigMenu_CreateOption_020c4718(&menu->image, 0x4a, 2, 0x400b);

    menu->cursorTag = FindLoadedElementById_020b8390(pool, 2);
    menu->helpTag = FindActiveRecordById_020b8184(pool, 0x10);
    layout = FindActiveRecordById_020b8184(pool, 0xd);
    menu->rowTags[0] = layout;
    for (i = 1; i < 6; i++) {
        void *tag;
        y = layout->y + i * 2;
        x = layout->x;
        tag = AddRecordFromTemplate_020b7ecc(pool, layout, nextId++, layout->userData);
        func_ov027_020b81e8(pool, tag, x, y);
        menu->rowTags[i] = tag;
    }
    menu->headerTag = FindActiveRecordById_020b8184(pool, 0x16);
    for (i = 0; i < 3; i++) {
        menu->pageTabs[i] = FindLoadedElementById_020b8390(pool, (u16)(i + 6));
    }
    menu->footerTag = FindActiveRecordById_020b8184(pool, 0x11);
    menu->arrowLeft = FindLoadedElementById_020b8390(pool, 3);
    menu->arrowRight = FindLoadedElementById_020b8390(pool, 4);
    menu->arrowLeftHelp = FindActiveRecordById_020b8184(pool, 0x12);
    menu->arrowRightHelp = FindActiveRecordById_020b8184(pool, 0x14);
    SetTagRecordArmed_020b83e8(pool, menu->cursorTag, TRUE);
    SetTagRecordArmed_020b83e8(pool, menu->arrowLeft, TRUE);
    SetTagRecordArmed_020b83e8(pool, menu->arrowRight, TRUE);
    func_ov039_020bc318(0, 4, 0xc, 0x1b, 2, func_ov039_020bc914());
    func_ov039_020bc414(1, 0, 0xc0);
    menu->tracker = pool;
    menu->dirty = 2;
    menu->pageChanged = 2;
    return TRUE;
}
