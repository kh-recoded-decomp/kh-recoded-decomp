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

typedef struct RowLayout {
    u8 pad_00[4];
    s16 y;
} RowLayout;

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

extern BOOL func_ov039_020bc0d4(void);
extern void func_ov027_020b81e0(void *tracker, void *tag, int y);
extern void SetTagRecordArmed_020b83e8(void *tracker, void *tag, BOOL arm);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *tag);
extern void func_ov027_020b845c(void *tracker, void *tag);
extern void ConfigMenu_Refresh_020c4a6c(ConfigMenu *menu);

void ConfigMenu_UpdateHelp_020c4608(ConfigMenu *menu)
{
    BOOL idle = func_ov039_020bc0d4() == 0 ? TRUE : FALSE;

    if (idle) {
        if (menu->helpShown == 0) {
            RowLayout *layout = menu->rowTags[menu->row];
            func_ov027_020b81e0(menu->tracker, menu->helpTag, layout->y);
            SetTagRecordArmed_020b83e8(menu->tracker, menu->cursorTag, FALSE);
            TagTracker_InvokeCallback_020b8210(menu->tracker, menu->helpTag);
            SetTagRecordArmed_020b83e8(menu->tracker, menu->arrowLeft, FALSE);
            TagTracker_InvokeCallback_020b8210(menu->tracker, menu->arrowLeftHelp);
            SetTagRecordArmed_020b83e8(menu->tracker, menu->arrowRight, FALSE);
            TagTracker_InvokeCallback_020b8210(menu->tracker, menu->arrowRightHelp);
            menu->helpShown = TRUE;
        }
    } else if (menu->helpShown != 0) {
        SetTagRecordArmed_020b83e8(menu->tracker, menu->cursorTag, TRUE);
        func_ov027_020b845c(menu->tracker, menu->cursorTag);
        SetTagRecordArmed_020b83e8(menu->tracker, menu->arrowLeft, TRUE);
        func_ov027_020b845c(menu->tracker, menu->arrowLeft);
        SetTagRecordArmed_020b83e8(menu->tracker, menu->arrowRight, TRUE);
        func_ov027_020b845c(menu->tracker, menu->arrowRight);
        menu->helpShown = FALSE;
    }
    ConfigMenu_Refresh_020c4a6c(menu);
}
