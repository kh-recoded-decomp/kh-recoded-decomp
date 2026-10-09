#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridPos {
    s16 x;
    s16 y;
} __attribute__((aligned(4))) GridPos;

typedef struct {
    fx32 x;
    fx32 y;
} Vec2Fx;

typedef struct {
    u8 pad_00[8];
    u16 flags;
} TouchState;

typedef struct {
    u8 width;
    u8 height;
    s8 offsetX;
    s8 offsetY;
} CursorFrame;

typedef struct {
    u16 index;
    u8 type;
} MatrixNode;

typedef struct MatrixMap MatrixMap;

typedef struct {
    u8 pad_00000[7];
    u8 needsRedraw;
    u8 pad_00008[0x10 - 0x8];
    BOOL started;
    BOOL cursorVisible;
    Vec2Fx origin;
    Vec2Fx cursor;
    GridPos cell;
    fx32 distance;
    s16 targetX;
    s16 targetY;
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0x40 - 0x3c];
    s16 offsetX;
    s16 offsetY;
    u8 pad_00044[0x50 - 0x44];
    Vec2Fx velocity;
    Vec2Fx drag;
    BOOL snapPending;
    BOOL snapAux;
    u8 pad_00068[0x70 - 0x68];
    BOOL freeScroll;
    BOOL locked;
    BOOL initialized;
    u8 pad_0007c[0x80 - 0x7c];
    BOOL closeRequested;
    u8 tabs[0x12dc4 - 0x84];
    u16 buttonHistory;
    u8 pad_12dc6[0x12dd0 - 0x12dc6];
    MatrixMap *map;
    MatrixNode *current;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    void *layout;
    u8 pad_131a8[0x13e64 - 0x131a8];
    u16 state;
    u8 pad_13e66[0x13e78 - 0x13e66];
    int phase;
    u8 pad_13e7c[0x13ea0 - 0x13e7c];
    BOOL dragMode;
    u8 pad_13ea4[0x13ecc - 0x13ea4];
    void *scrollBar;
    u8 pad_13ed0[0x174e4 - 0x13ed0];
    Vec2Fx barPos;
    u8 pad_174ec[0x174f4 - 0x174ec];
    int popup;
    int popupBusy;
    u8 pad_174fc[0x17520 - 0x174fc];
    int popupActive;
    int popupEntry;
} MatrixMenu;

extern u16 data_020604fc;

extern TouchState *GetMenuInputState(void);
extern BOOL IsStatePhaseActive(void);
extern BOOL ShowNextUnlockNotice(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);
extern int HandleTabTouch(void *tabs, int currentTab, BOOL allowChange);
extern int UpdateMatrixOptionMenu(MatrixMenu *menu);
extern int func_ov075_020c709c(MatrixMenu *menu);
extern u32 func_ov075_020c7bdc(int value);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u32 func_ov075_020c7bf4(int value);
extern int ScaleMatrixInput(int value, int useHalfScale);
extern void ScrollMatrixView(MatrixMenu *menu);
extern void func_ov027_020b91e8(void *panel, void *element, Vec2Fx *pos, int mode);
extern GridPos FindNearestReachableNode(MatrixMap *grid, GridPos pos, MatrixNode **outNode, BOOL skipCurrent);
extern void ShowEntryHeaderMessage(MatrixMenu *menu, MatrixNode *node);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern CursorFrame *GetMatrixModeLabel(int mode);
extern u32 func_ov075_020c7d14(void *tabs);
extern u32 func_ov075_020c7d1c(void *tabs);
extern void ResetMatrixCamera(void);
extern void DrawMatrixMenu(MatrixMenu *menu);
extern void UpdateMatrixEventAnimation(MatrixMenu *menu);
extern void func_ov075_020d076c(void *tabs);
extern void ToggleSharedStateFlag(int flag);
extern void SetMenuStateNoParam(int state);
extern void RuntimeState_SetCondition(int value);
extern void SetUnlockableElementsVisible(void *layout, BOOL visible);
extern void SetMatrixDescription(MatrixMenu *menu, int index);
extern void DrawMatrixDescriptionText(MatrixMenu *menu);

static inline fx32 GetDistance(fx32 fromX, fx32 fromY, fx32 toX, fx32 toY)
{
    fx32 dx = toX - fromX;
    fx32 dy = toY - fromY;
    return FX_Sqrt(func_ov075_020c7bdc(dx) + func_ov075_020c7bdc(dy));
}

void UpdateMatrixMenuView(MatrixMenu *menu)
{
    u16 touchPhase;
    int moved;
    int len;
    int snapLen;
    fx32 stepX;
    fx32 snapStepX;

    touchPhase = GetMenuInputState()->flags & 3;
    menu->buttonHistory = IsStatePhaseActive() ? 0 : ((data_020604fc & 0x800) ? 1 : 0) | (menu->buttonHistory << 1);
    if (!IsStatePhaseActive() && menu->initialized == 0) {
        menu->initialized = 1;
        if (menu->popup == -1) {
            ShowNextUnlockNotice(menu, FALSE, FALSE);
        }
    }
    if (menu->state != 0 || HandleTabTouch(menu->tabs, 1, TRUE) >= 0) {
        moved = 0;
    } else {
        if (menu->dragMode) {
            moved = UpdateMatrixOptionMenu(menu);
        } else {
            moved = func_ov075_020c709c(menu);
        }
        if (touchPhase == 2) {
            menu->velocity.x = menu->drag.x;
            menu->velocity.y = menu->drag.y;
            menu->drag.x = 0;
            menu->drag.y = 0;
        } else if (touchPhase == 3) {
            menu->drag.x = menu->velocity.x;
            menu->drag.y = menu->velocity.y;
        }
    }

    if (menu->popup > 0 || menu->popupActive > 0 || menu->phase != 0) {
        Vec2Fx pos;
        fx32 targetX = menu->targetX << 12;
        fx32 targetY = menu->targetY << 12;
        fx32 dist;
        fx32 stepY;
        BOOL inX;
        BOOL visible;
        BOOL inY;

        {
            fx32 dx = targetX - menu->scrollX;
            fx32 dy = targetY - menu->scrollY;

            len = 0;
            dist = FX_Sqrt(func_ov075_020c7bdc(dx) + func_ov075_020c7bdc(dy));
        }
        menu->distance = dist;
        if (dist != 0) {
            len = dist / 4;
            dist = FX_Div(len, dist);
        }
        stepX = FX_Mul(targetX - menu->scrollX, dist);
        stepY = FX_Mul(targetY - menu->scrollY, dist);
        if (func_ov075_020c7bf4(stepX) < 0x200) {
            stepX = 0;
            menu->scrollX = targetX;
        }
        if (func_ov075_020c7bf4(stepY) < 0x200) {
            stepY = 0;
            menu->scrollY = targetY;
        }
        if (len >= 0x200) {
            menu->scrollX += stepX;
            menu->scrollY += stepY;
        }
        pos = menu->origin;
        pos.x += targetX - menu->scrollX;
        pos.y += targetY - menu->scrollY;
        if (pos.x & 0xfff) {
            pos.x = (pos.x & ~0xfff) + 0x1000;
        }
        if (pos.y & 0xfff) {
            pos.y = (pos.y & ~0xfff) + 0x1000;
        }
        visible = FALSE;
        inX = FALSE;
        inY = FALSE;
        if (pos.y > -0x10000 && pos.y <= 0xd0000) {
            inY = TRUE;
        }
        if (inY && pos.x > -0x10000) {
            inX = TRUE;
        }
        if (inX && pos.x <= 0x110000) {
            visible = TRUE;
        }
        if (visible && menu->closeRequested == 0) {
            if (pos.x <= 0x68000) {
                visible = TRUE;
            } else {
                visible = FALSE;
            }
        }
        menu->cursor = pos;
        menu->cursorVisible = visible;
    } else if (menu->freeScroll) {
        ScrollMatrixView(menu);
        menu->barPos.x = (menu->scrollX >> 2) + 0x20000;
        menu->barPos.y = (menu->scrollY >> 2) + 0x18000;
        func_ov027_020b91e8(menu->layout, menu->scrollBar, &menu->barPos, 0);
        menu->velocity.y = 0;
        menu->velocity.x = 0;
    } else if ((menu->velocity.x | menu->velocity.y) != 0 || moved) {
        menu->scrollX += menu->velocity.x;
        menu->scrollY += menu->velocity.y;
        if (menu->scrollX < 0) {
            menu->velocity.x = 0;
            menu->scrollX = 0;
        } else if (menu->scrollX > 0x2f0000) {
            menu->scrollX = 0x2f0000;
            menu->velocity.x = 0;
        }
        if (menu->scrollY < 0) {
            menu->velocity.y = 0;
            menu->scrollY = 0;
        } else if (menu->scrollY > 0x230000) {
            menu->scrollY = 0x230000;
            menu->velocity.y = 0;
        }
        if (touchPhase == 3) {
            menu->velocity.x = 0;
            menu->velocity.y = 0;
        } else {
            if (func_ov075_020c7bf4(menu->velocity.x) < 0x800) {
                menu->velocity.x = 0;
            } else {
                menu->velocity.x = menu->velocity.x - ScaleMatrixInput(menu->velocity.x, moved);
            }
            if (func_ov075_020c7bf4(menu->velocity.y) < 0x800) {
                menu->velocity.y = 0;
            } else {
                menu->velocity.y = menu->velocity.y - ScaleMatrixInput(menu->velocity.y, moved);
            }
        }
    } else {
        Vec2Fx pos;
        MatrixNode *node;
        GridPos cell;
        CursorFrame *frame;
        int cellX;
        int cellY;
        fx32 targetX;
        fx32 targetY;
        fx32 dist;
        fx32 stepY;
        BOOL visible;
        BOOL inX;
        BOOL inY;

        snapLen = 0;
        if (menu->snapPending) {
            node = menu->current;
            menu->snapAux = snapLen;
            menu->snapPending = snapLen;
            cell.x = menu->scrollX >> 16;
            cell.y = menu->scrollY >> 16;
            menu->cell = FindNearestReachableNode(menu->map, cell, &node, snapLen);
            if (node != menu->current) {
                menu->current = node;
            }
            ShowEntryHeaderMessage(menu, menu->current);
            ShowNextUnlockNotice(menu, TRUE, FALSE);
            PlaySoundEffect(1, 0);
            SetSecondaryElementEnabled(FALSE);
        }
        frame = GetMatrixModeLabel(menu->current->type);
        cellX = (menu->cell.x + menu->offsetX) * 16 + 8 + ((frame->width - 16) >> 1) + frame->offsetX;
        cellY = (menu->cell.y + menu->offsetY) * 16 + ((frame->height - 16) >> 1) + frame->offsetY;
        targetX = cellX << 12;
        targetY = cellY << 12;
        menu->targetY = cellY;
        menu->targetX = cellX;
        dist = GetDistance(menu->scrollX, menu->scrollY, targetX, targetY);
        if (dist != 0) {
            snapLen = dist / 4;
            dist = FX_Div(snapLen, dist);
        }
        snapStepX = FX_Mul(targetX - menu->scrollX, dist);
        stepY = FX_Mul(targetY - menu->scrollY, dist);
        if (func_ov075_020c7bf4(snapStepX) < 0x200) {
            snapStepX = 0;
            menu->scrollX = targetX;
        }
        if (func_ov075_020c7bf4(stepY) < 0x200) {
            stepY = 0;
            menu->scrollY = targetY;
        }
        if (snapLen < 0x200) {
            if (!IsStatePhaseActive() && menu->locked == 0 && menu->popupEntry == 0 && menu->popupBusy == 0 &&
                menu->state == 0 && func_ov075_020c7d14(menu->tabs) == 0) {
                SetSecondaryElementEnabled(TRUE);
            }
        } else {
            menu->scrollX += snapStepX;
            menu->scrollY += stepY;
        }
        pos = menu->origin;
        pos.x += targetX - menu->scrollX - (menu->offsetX << 16);
        pos.y += targetY - menu->scrollY - (menu->offsetY << 16);
        if (pos.x & 0xfff) {
            pos.x = (pos.x & ~0xfff) + 0x1000;
        }
        if (pos.y & 0xfff) {
            pos.y = (pos.y & ~0xfff) + 0x1000;
        }
        visible = FALSE;
        inX = FALSE;
        inY = FALSE;
        if (pos.y > -0x10000 && pos.y <= 0xd0000) {
            inY = TRUE;
        }
        if (inY && pos.x > -0x10000) {
            inX = TRUE;
        }
        if (inX && pos.x <= 0x110000) {
            visible = TRUE;
        }
        if (visible && func_ov075_020c7d1c(menu->tabs)) {
            visible = TRUE;
            if (pos.x > 0x68000) {
                visible = FALSE;
            }
        }
        menu->cursor = pos;
        menu->cursorVisible = visible;
    }

    ResetMatrixCamera();
    if (menu->freeScroll == 0) {
        DrawMatrixMenu(menu);
        UpdateMatrixEventAnimation(menu);
    }
    func_ov075_020d076c(menu->tabs);
    if (menu->needsRedraw != 0) {
        menu->needsRedraw--;
        if (menu->needsRedraw != 0) {
            ToggleSharedStateFlag(1);
            ShowEntryHeaderMessage(menu, menu->current);
            if (menu->started == 0) {
                SetMenuStateNoParam(0);
                RuntimeState_SetCondition(1);
                menu->started = 1;
                if (menu->popup == 0 || ShowNextUnlockNotice(menu, FALSE, TRUE)) {
                    SetUnlockableElementsVisible(menu->layout, FALSE);
                    SetMatrixDescription(menu, -1);
                }
            }
        }
        DrawMatrixDescriptionText(menu);
    }
}
