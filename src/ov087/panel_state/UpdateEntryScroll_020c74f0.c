#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    int entryCount;
    fx32 scrollX;
    fx32 scrollSpeed;
    u8 pad_014[0xb5c];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0xc];
    BOOL brightened;
    u8 pad_bb4[0x24];
    u64 lastRepeatTick;
} PanelScene;

extern u16 data_020604fc;
extern u16 data_02060500;

extern u64 OS_GetTick_02003fd4(void);
extern void *func_ov039_020bc1bc(void);
extern BOOL func_ov039_020bc0d4(void);
extern void SetScreenBrightness_020bc648(int brightness);
extern void RefreshChoiceMenu_020c4d6c(PanelScene *scene, BOOL keepFirst);
extern void func_ov087_020c5200(PanelScene *scene);
extern void func_ov087_020c548c(PanelScene *scene);
extern void *func_ov027_020b90f4(void *container);
extern void func_ov087_020c44a4(PanelScene *scene, void *widget);
extern void SetWidgetRootDpadEnabled_020b9874(void *root, BOOL enabled);
extern void RefreshSelectedEntryInfo_020c5ef0(PanelScene *scene, BOOL playSound);
extern void func_ov087_020c6c84(PanelScene *scene);

void UpdateEntryScroll_020c74f0(PanelScene *scene)
{
    int oldCursor;
    BOOL scrollLeft;
    BOOL scrollRight;
    u64 tick;

    scrollLeft = FALSE;
    scrollRight = FALSE;
    oldCursor = scene->cursor;
    tick = OS_GetTick_02003fd4();
    void *container;
    BOOL ready;
    fx32 scroll;

    container = func_ov039_020bc1bc();
    if (scene->brightened) {
        if (!func_ov039_020bc0d4()) {
            SetScreenBrightness_020bc648(-8);
            scene->brightened = FALSE;
        }
    } else if (func_ov039_020bc0d4()) {
        SetScreenBrightness_020bc648(0);
        scene->brightened = TRUE;
    }
    if (scene->stack[scene->depth].stateId != 0x10 &&
        (tick == 0 || tick - scene->lastRepeatTick >= 0x3fec4)) {
        ready = TRUE;
    } else {
        ready = FALSE;
    }
    if (data_020604fc & 0x220) {
        if (ready) {
            scrollLeft = TRUE;
            if (data_02060500 & 0x220) {
                scene->lastRepeatTick = tick;
            }
        }
    } else if (data_020604fc & 0x110) {
        if (ready) {
            scrollRight = TRUE;
            if (data_02060500 & 0x110) {
                scene->lastRepeatTick = tick;
            }
        }
    } else {
        scene->lastRepeatTick = 0;
    }
    switch (scene->stack[scene->depth].stateId) {
    case 1:
    case 2:
    case 3:
    case 0x10:
        if (func_ov039_020bc0d4() && scrollLeft) {
            scroll = scene->scrollX + 0x2800;
            scene->scrollX = scroll;
            scene->scrollSpeed = 0x2800;
            if (scroll >= 0xc800) {
                scene->scrollX = scroll - 0xc800;
                scene->cursor = (scene->entryCount + scene->cursor - 1) % scene->entryCount;
                RefreshSelectedEntryInfo_020c5ef0(scene, TRUE);
            }
        } else if (func_ov039_020bc0d4() && scrollRight) {
            scroll = scene->scrollX - 0x2800;
            scene->scrollX = scroll;
            scene->scrollSpeed = -0x2800;
            if (scroll <= -0xc800) {
                scene->scrollX = scroll + 0xc800;
                scene->cursor = (scene->cursor + 1) % scene->entryCount;
                RefreshSelectedEntryInfo_020c5ef0(scene, TRUE);
            }
        } else if (scene->scrollX != 0) {
            scene->scrollX += scene->scrollSpeed;
            if (scene->scrollX <= -0xc800) {
                scene->cursor = (scene->cursor + 1) % scene->entryCount;
                scene->scrollSpeed = 0;
                scene->scrollX = 0;
                RefreshSelectedEntryInfo_020c5ef0(scene, TRUE);
            }
            if (scene->scrollX >= 0xc800) {
                scene->cursor = (scene->entryCount + scene->cursor - 1) % scene->entryCount;
                scene->scrollSpeed = 0;
                scene->scrollX = 0;
                RefreshSelectedEntryInfo_020c5ef0(scene, TRUE);
            }
        }
        if (oldCursor != scene->cursor) {
            switch (scene->stack[scene->depth].stateId) {
            case 1:
                RefreshChoiceMenu_020c4d6c(scene, TRUE);
                break;
            case 2:
                func_ov087_020c5200(scene);
                break;
            case 3:
                func_ov087_020c548c(scene);
                break;
            default:
                goto done;
            }
            func_ov087_020c44a4(scene, func_ov027_020b90f4(func_ov039_020bc1bc()));
        }
        break;
    }
done:
    if (func_ov039_020bc0d4()) {
        if (scene->scrollX == 0) {
            SetWidgetRootDpadEnabled_020b9874(container, TRUE);
        } else {
            SetWidgetRootDpadEnabled_020b9874(container, FALSE);
        }
    }
    func_ov087_020c6c84(scene);
}
