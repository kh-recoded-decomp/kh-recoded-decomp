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
} ConfigMenu;

extern void CallVirtualHandlerSlot1_02001574(void *list, int arg);
extern void func_0200160c(void *list, u32 x, u32 y, u32 color, u32 flags, const void *text, void *font, u32 width);
extern void *func_ov039_020bc9ac(void);
extern void Text_UploadTileBuffer_02001520(void *list);

void ConfigMenu_DrawText_020c4928(ConfigMenu *menu)
{
    ConfigPage *pages = menu->pages;
    int pageIndex = menu->page;
    ConfigPage *page = &pages[pageIndex];
    ConfigOption *current = page->options[menu->row];
    int i = 0;
    const void *title;
    const void *label;
    const void *name;
    const void *description;

    CallVirtualHandlerSlot1_02001574(menu->objectLists[1], 0);
    CallVirtualHandlerSlot1_02001574(menu->objectLists[2], 0);
    CallVirtualHandlerSlot1_02001574(menu->objectLists[3], 0);
    CallVirtualHandlerSlot1_02001574(menu->objectLists[4], 0);
    title = page->title;
    func_0200160c(menu->objectLists[1], 0, 3, 2, 8, title, func_ov039_020bc9ac(), 0x68);
    if (i < pages[pageIndex].rowCount) {
        do {
            label = page->options[i]->label;
            func_0200160c(menu->objectLists[2], 0, i * 16 + 3, 2, 8, label, func_ov039_020bc9ac(), 0x58);
            name = page->options[i]->choices[page->options[i]->value].name;
            func_0200160c(menu->objectLists[3], 0, i * 16 + 3, 2, 8, name, func_ov039_020bc9ac(), 0x58);
            i++;
        } while (i < page->rowCount);
    }
    description = current->choices[current->value].description;
    func_0200160c(menu->objectLists[4], 2, 0, 2, 8, description, func_ov039_020bc9ac(), 0x100);
    Text_UploadTileBuffer_02001520(menu->objectLists[0]);
    Text_UploadTileBuffer_02001520(menu->objectLists[1]);
    Text_UploadTileBuffer_02001520(menu->objectLists[2]);
    Text_UploadTileBuffer_02001520(menu->objectLists[3]);
    Text_UploadTileBuffer_02001520(menu->objectLists[4]);
}
