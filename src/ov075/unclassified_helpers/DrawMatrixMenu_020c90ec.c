#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

typedef struct {
    u16 width;
    u16 height;
} CellSize;

typedef struct {
    s16 pivotX;
    s16 pivotY;
    s32 angle;
} QuadRotation;

typedef struct {
    u8 width;
    u8 height;
    s8 offsetX;
    s8 offsetY;
} CursorFrame;

typedef struct {
    s16 x;
    s16 y;
} Point16;

typedef struct {
    u8 cols;
    u8 rows;
    u8 pad_02[2];
    u16 itemCount;
} GridDims;

typedef struct {
    u16 id;
    u8 type;
    s8 linkIndex;
    s16 slotId;
    u16 groupBit;
    u8 placed;
    u8 hidden;
} GridItem;

typedef struct {
    u32 linkCount;
    u8 pad_0004[0x14];
    GridItem *links[32];
    GridDims *dims;
    GridItem *cells[(0x1b9c - 0x9c) / 4];
    GridItem *items[(0x24dc - 0x1b9c) / 4];
    s16 groupValues[(0x2528 - 0x24dc) / 2];
    u8 groupOf[0x2be8 - 0x2528];
    u8 unlockLevel[1];
} Grid;

typedef struct {
    u8 pad_00[0x10];
    int iconIndex;
} SlotRecord;

typedef struct {
    u8 pad_00[8];
    SlotRecord *record;
} SlotCount;

typedef struct {
    u8 pad_00[3];
    s8 focusOffsetY;
} UnlockNotice;

typedef struct {
    u8 data[0x104];
} SceneNode;

typedef struct {
    Point16 points[16];
    u8 length;
    u8 step;
    u8 reverse;
    u8 delay;
} PipeTrail;

typedef struct {
    s16 left;
    s16 top;
    s16 frameLeft;
    s16 frameTop;
    s16 frameRight;
    s16 frameBottom;
} CursorRect;

typedef struct {
    u8 pad_00000[0x14];
    s32 cursorEnabled;
    u8 pad_00018[8];
    fx32 cursorX;
    fx32 cursorY;
    u8 pad_00028[0xc];
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0xc];
    u32 frameCounter;
    u8 pad_0004c[0x28];
    BOOL dialogOpen;
    u8 pad_00078[8];
    s32 closeRequested;
    u8 pad_00084[8];
    BOOL cursorSuppressed;
    u8 pad_00090[0x28];
    MenuImage slotIcons[165];
    u8 pad_00874[8];
    SlotCount slotCounts[(0x11f40 - 0x87c) / 12];
    s32 lastInputResult;
    u8 pad_11f44[0x12dd0 - 0x11f44];
    Grid *grid;
    GridItem *selectedItem;
    u8 pad_12dd8[0x131a8 - 0x12dd8];
    u32 cursorBlink;
    CursorRect rect;
    MenuImage cursorImage;
    MenuImage cornerImage;
    MenuImage gateImageA;
    MenuImage gateImageB;
    MenuImage chestImage;
    MenuImage markerImages[2];
    MenuImage wideImages[9];
    MenuImage pipeImagesA[9];
    MenuImage pipeImagesB[9];
    MenuImage bridgeImages[9];
    MenuImage linkImages[9];
    MenuImage objectImages[5];
    SceneNode figureNode;
    SceneNode medalNode;
    MenuImage clockImage;
    SceneNode bonusNode;
    SceneNode gaugeNode;
    MenuImage menuFooter;
    MenuImage menuSideLeft;
    MenuImage menuHeader;
    MenuImage menuSideRight;
    MenuImage menuDial;
    MenuImage figureBar;
    MenuImage medalLights;
    MenuImage clockHand;
    MenuImage gaugeNeedle;
    u8 pad_138ec[0x13e04 - 0x138ec];
    MenuImage trailImages[8];
    u16 phase;
    u8 pad_13e66[0x13e74 - 0x13e66];
    u32 phaseTimer;
    u8 pad_13e78[0x13e8c - 0x13e78];
    u8 *menuRotation;
    u8 *clockHour;
    u8 pad_13e94[4];
    u8 *medalBits;
    u8 *figureLevel;
    int currentMode;
    u8 pad_13ea4[0x13eb0 - 0x13ea4];
    s16 cursorShiftX;
    s16 cursorShiftY;
    u8 pad_13eb4[4];
    s16 gaugeShiftX;
    s16 gaugeShiftY;
    u8 pad_13ebc[4];
    int gaugeTarget;
    u8 pad_13ec4[0x174f4 - 0x13ec4];
    s32 introState;
    u8 pad_174f8[0x17520 - 0x174f8];
    s32 noticeStep;
    UnlockNotice *notice;
    u8 pad_17528[5];
    u8 animTick;
    u8 pad_1752e[0x17574 - 0x1752e];
    PipeTrail trails[12];
    u32 trailMask;
} MatrixMenu;

typedef struct {
    u8 pad_0000[0x2c58];
    u32 groupFlags;
    u32 unlockBits[1];
    u16 unlockMask;
    u8 pad_2c62[5];
    u8 unlockCount;
} SaveBlock;

extern SaveBlock *data_0205fe0c;
extern const CursorFrame data_ov075_020d1454[];
extern const CellSize data_ov075_020d1488;
extern const CellSize data_ov075_020d148c;
extern const CellSize data_ov075_020d1490;
extern const CellSize data_ov075_020d1494;
extern const CellSize data_ov075_020d1498;
extern const CellSize data_ov075_020d149c;
extern const QuadRotation data_ov075_020d14b0;
extern const QuadRotation data_ov075_020d14b8;

extern BOOL func_ov039_020bc0d4(void);
extern u32 func_01ff80d4(void);
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);
extern int Anim_GetFrame_0202f4a0(void *node, int channel);
extern int *func_01ffb2f8(void *node, int channel, int frame);
extern BOOL IsMenuModeUnlocked_020c4324(int mode);
extern u16 GetModeLabelColor_020cc9b0(MatrixMenu *menu, int mode);
extern void DrawImageQuadIfVisible_020d0cd8(const MenuImage *image, int x, int y, int depth, u16 color, BOOL highlighted);
extern void DrawImageQuadWithIdIfVisible_020d0d2c(const MenuImage *image, int x, int y, int depth, u16 color, u32 polygonId);
extern void DrawRotatedImageQuadIfVisible_020d0d80(const MenuImage *image, int x, int y, int depth, u16 color,
                                                   BOOL highlighted, const QuadRotation *rotation);
extern void DrawCellQuadIfVisible_020d0dd4(const MenuImage *image, int x, int y, int depth, u16 color, CellSize cell,
                                           BOOL highlighted);
extern void DrawNodeAtInvertedY_020d0e30(void *node, u32 x, int y);
extern void DrawMenuImageCentered_020d10e0(const MenuImage *images, u32 select, u32 pos, fx32 depth);

static inline BOOL IsInputLocked(void)
{
    return !func_ov039_020bc0d4();
}

static inline BOOL IsLinkUnlocked(int index)
{
    return GetPackedBitMask(data_0205fe0c->unlockBits, index) != 0;
}

static inline BOOL IsItemUnlocked(GridItem *item)
{
    return item->type == 1 && (data_0205fe0c->unlockMask & (1 << item->groupBit));
}

static inline void DrawSlotIcon(MatrixMenu *menu, int icon, int color, int x, int y)
{
    DrawMenuImageCentered_020d10e0(menu->slotIcons, ((u16)icon << 16) | (u16)color, (x << 16) | (u16)y, 0x200000);
}

static inline BOOL IsModeSelected(MatrixMenu *menu, int mode)
{
    return menu->currentMode == mode;
}

void DrawMatrixMenu_020c90ec(MatrixMenu *menu)
{
    BOOL idle = TRUE;
    GridDims *dims = menu->grid->dims;
    GridItem **link = menu->grid->links;
    u8 cols = dims->cols;
    u16 level = data_0205fe0c->unlockCount;
    GridItem **items;
    u8 *unlockLevel;
    CellSize corner;
    const CursorFrame *frame;
    int frameIndex;
    u16 count;
    int i;

    if (!IsInputLocked() && menu->lastInputResult != 1) {
        idle = FALSE;
    }
    items = menu->grid->items;
    unlockLevel = menu->grid->unlockLevel;
    corner = data_ov075_020d149c;
    menu->frameCounter = func_01ff80d4();

    frameIndex = menu->selectedItem->type;
    if (frameIndex < 3 || frameIndex >= 14) {
        frameIndex = 0;
    } else {
        frameIndex -= 2;
    }
    frame = &data_ov075_020d1454[frameIndex];
    menu->rect.left = menu->cursorX / 4096 - (frame->width >> 1) - frame->offsetX;
    menu->rect.top = menu->cursorY / 4096 - frame->offsetY;
    if (menu->closeRequested != 0) {
        menu->rect.top += menu->notice->focusOffsetY;
    }
    menu->rect.frameLeft = menu->rect.left;
    menu->rect.frameRight = menu->rect.left + frame->width;
    menu->rect.frameTop = menu->rect.top - (frame->height >> 1);
    menu->rect.frameBottom = menu->rect.frameTop + frame->height;
    menu->rect.left -= (s16)(menu->cursorBlink / 15);

    if (menu->introState < 0 && (menu->noticeStep == 0 || menu->closeRequested != 0) && menu->dialogOpen == 0
        && menu->cursorEnabled != 0 && menu->cursorSuppressed == 0 && menu->phase == 0) {
        if (menu->currentMode == 0) {
            if (!idle) {
                DrawImageQuadIfVisible_020d0cd8(&menu->cursorImage, menu->rect.left, menu->rect.top - 8, 0x280, 0x7fff, 0);
            }
            DrawCellQuadIfVisible_020d0dd4(&menu->cornerImage, menu->rect.frameLeft + 8, menu->rect.frameTop, 0x280, 0x7fff,
                                           corner, 0);
            corner.height++;
            DrawCellQuadIfVisible_020d0dd4(&menu->cornerImage, menu->rect.frameRight, menu->rect.frameTop, 0x280, 0x7fff,
                                           corner, 0);
            corner.height++;
            DrawCellQuadIfVisible_020d0dd4(&menu->cornerImage, menu->rect.frameRight, menu->rect.frameBottom - 8, 0x280,
                                           0x7fff, corner, 0);
            corner.height++;
            DrawCellQuadIfVisible_020d0dd4(&menu->cornerImage, menu->rect.frameLeft + 8, menu->rect.frameBottom - 8, 0x280,
                                           0x7fff, corner, 0);
        } else if (!idle) {
            DrawImageQuadIfVisible_020d0cd8(&menu->cursorImage, menu->rect.left + menu->cursorShiftX,
                                            menu->rect.top + menu->cursorShiftY - 8, 0x280, 0x7fff, 0);
        }
    }

    for (count = menu->grid->linkCount; count != 0; count--, link++) {
        if (!IsLinkUnlocked(link - menu->grid->links)) {
            s16 id = (*link)->id;
            if (unlockLevel[id] <= level) {
                u16 variant = (*link)->linkIndex == 5;
                DrawImageQuadIfVisible_020d0cd8(&menu->markerImages[variant],
                                                (s16)((id % cols) * 16 + 0x80 - (menu->scrollX >> 12)),
                                                (s16)((id / cols) * 16 + 0x58 - (menu->scrollY >> 12)), 400, 0x7fff, 0);
            }
        }
    }

    for (count = dims->itemCount; count != 0; count--, items++) {
        GridItem *item = *items;
        u16 id = item->id;
        s16 x = (id % cols) * 16 + 0x80 - (menu->scrollX >> 12);
        s16 y = (id / cols) * 16 + 0x58 - (menu->scrollY >> 12);
        fx32 nodeX = 0;
        fx32 nodeY = 0;
        u16 color = 0x7fff;
        BOOL highlight = FALSE;
        CellSize cell = {0, 0};
        const MenuImage *image = NULL;
        SceneNode *node = NULL;
        int links;

        if (unlockLevel[item->id] > level) {
            continue;
        }
        if (item->slotId >= 0) {
            highlight = TRUE;
            if (!IsItemUnlocked(item)) {
                color = 0x7bde;
            }
            DrawSlotIcon(menu, menu->slotCounts[item->slotId].record->iconIndex, color, x, y);
        }
        switch (item->type) {
        case 1:
            image = &menu->gateImageA;
            if (item->hidden == 0 && item->slotId < 0) {
                color = 0x3def;
            }
            break;
        case 2:
            image = &menu->gateImageB;
            if (item->hidden == 0 && item->slotId < 0) {
                color = 0x3def;
            }
            break;
        case 3:
            image = &menu->chestImage;
            color = 0x77bd;
            highlight = TRUE;
            break;
        case 14:
            image = menu->pipeImagesA;
            cell.width = 4;
            break;
        case 15:
            image = menu->pipeImagesA;
            cell.width = 4;
            cell.height = 1;
            break;
        case 16:
            image = menu->pipeImagesA;
            cell.width = 4;
            cell.height = 2;
            break;
        case 17:
            image = menu->pipeImagesA;
            cell.width = 4;
            cell.height = 3;
            break;
        case 18:
            image = menu->wideImages;
            cell.width = 2;
            break;
        case 19:
            image = menu->wideImages;
            cell.width = 2;
            cell.height = 1;
            break;
        case 20:
            image = menu->pipeImagesB;
            cell.width = 4;
            break;
        case 21:
            image = menu->pipeImagesB;
            cell.width = 4;
            cell.height = 1;
            break;
        case 22:
            image = menu->pipeImagesB;
            cell.width = 4;
            cell.height = 2;
            break;
        case 23:
            image = menu->pipeImagesB;
            cell.width = 4;
            cell.height = 3;
            break;
        case 24:
            image = menu->bridgeImages;
            break;
        case 6: {
            s16 value = menu->grid->groupValues[item->groupBit];
            int variant;
            if (value >= 0xf8 && value <= 0xfb) {
                variant = 3;
            } else {
                variant = 0;
            }
            image = &menu->objectImages[variant];
            cell.width = 2;
            cell.height = (data_0205fe0c->groupFlags & (1 << item->groupBit)) ? 1 : 0;
            if (item->placed) {
                color = 0x3def;
            }
            break;
        }
        case 7:
            image = &menu->objectImages[1];
            if (item->placed) {
                color = 0x3def;
            }
            break;
        case 8:
            image = &menu->objectImages[2];
            if (item->placed) {
                color = 0x3def;
            }
            break;
        case 9: {
            QuadRotation rotation;
            BOOL active;
            u16 labelColor;
            s16 centerX;
            s16 centerY;
            image = &menu->objectImages[4];
            rotation = data_ov075_020d14b0;
            active = menu->currentMode == 1;
            labelColor = GetModeLabelColor_020cc9b0(menu, 1);
            rotation.angle = (*menu->menuRotation & 3) << 14;
            centerY = y + 40;
            centerX = x + 40;
            DrawRotatedImageQuadIfVisible_020d0d80(&menu->menuDial, centerX - 32, centerY - 32, 0x26c, labelColor, active,
                                                   &rotation);
            DrawImageQuadIfVisible_020d0cd8(&menu->menuFooter, centerX - 32, centerY + 40, 0x26c, 0x7fff, 0);
            DrawImageQuadIfVisible_020d0cd8(&menu->menuSideLeft, centerX - 104, centerY - 4, 0x26c, 0x7fff, 0);
            DrawImageQuadIfVisible_020d0cd8(&menu->menuHeader, centerX - 32, centerY - 48, 0x26c, 0x7fff, 0);
            DrawImageQuadIfVisible_020d0cd8(&menu->menuSideRight, centerX + 40, centerY - 4, 0x26c, 0x7fff, 0);
            break;
        }
        case 10: {
            BOOL active;
            u16 labelColor;
            node = &menu->figureNode;
            x += 0x60;
            y += 0x10;
            nodeX += 0x800;
            active = IsModeSelected(menu, 5);
            labelColor = GetModeLabelColor_020cc9b0(menu, 5);
            DrawImageQuadIfVisible_020d0cd8(&menu->figureBar, x - 0x57 + *menu->figureLevel * 160 / 100, y - 12, 0x26c,
                                            labelColor, active);
            break;
        }
        case 11: {
            CellSize bits;
            BOOL active;
            u16 labelColor;
            node = &menu->medalNode;
            x += 0x30;
            y += 0x30;
            bits = data_ov075_020d1494;
            active = IsModeSelected(menu, 4);
            labelColor = GetModeLabelColor_020cc9b0(menu, 4);
            bits.height = *menu->medalBits & 1;
            DrawCellQuadIfVisible_020d0dd4(&menu->medalLights, x - 32, y + 8, 0x26c, labelColor, bits, active);
            bits.height = (*menu->medalBits >> 1) & 1;
            DrawCellQuadIfVisible_020d0dd4(&menu->medalLights, x - 8, y + 8, 0x26c, labelColor, bits, active);
            bits.height = (*menu->medalBits >> 2) & 1;
            DrawCellQuadIfVisible_020d0dd4(&menu->medalLights, x + 16, y + 8, 0x26c, labelColor, bits, active);
            break;
        }
        case 12: {
            QuadRotation rotation;
            BOOL active;
            u16 labelColor;
            int clockColor;
            x += 0x28;
            y += 0x28;
            rotation = data_ov075_020d14b8;
            active = IsModeSelected(menu, 2);
            labelColor = GetModeLabelColor_020cc9b0(menu, 2);
            rotation.angle = (u16)((*menu->clockHour << 16) / 90);
            DrawRotatedImageQuadIfVisible_020d0d80(&menu->clockHand, x - 32, y - 32, 0x26c, labelColor, active, &rotation);
            if (IsMenuModeUnlocked_020c4324(2) && ((menu->phase & ~0xff) != 0x600 || menu->phaseTimer > 0x10)) {
                clockColor = 0x7fff;
            } else {
                clockColor = 0x3def;
            }
            DrawImageQuadIfVisible_020d0cd8(&menu->clockImage, x - 0x27, y - 0x27, 0x26c, clockColor, 0);
            break;
        }
        case 25:
            node = &menu->bonusNode;
            x += 0x60;
            y += 0x10;
            nodeX += 0x1800;
            nodeY += 0x1800;
            break;
        case 13: {
            int gaugeFrame;
            BOOL active;
            u16 labelColor;
            node = &menu->gaugeNode;
            x += 0x40;
            y += 0x30;
            gaugeFrame = Anim_GetFrame_0202f4a0(&menu->gaugeNode, 3);
            active = IsModeSelected(menu, 3);
            labelColor = GetModeLabelColor_020cc9b0(menu, 3);
            DrawImageQuadIfVisible_020d0cd8(&menu->gaugeNeedle, x - 0x38 + menu->gaugeShiftX, y - 7 + menu->gaugeShiftY,
                                            0x26c, labelColor, active);
            if (gaugeFrame < menu->gaugeTarget) {
                gaugeFrame += 0x800;
            } else if (gaugeFrame > menu->gaugeTarget) {
                gaugeFrame -= 0x800;
            }
            func_01ffb2f8(&menu->gaugeNode, 3, gaugeFrame);
            break;
        }
        }

        if (item->type >= 14 && item->type <= 24) {
            u16 linkFrame;
            links = 0;
            linkFrame = item->placed == 0 ? (menu->animTick >> 2) & 7 : 8;
            image += linkFrame;
            switch (item->type) {
            case 14:
                links = 3;
                break;
            case 15:
                links = 6;
                break;
            case 16:
                links = 12;
                break;
            case 17:
                links = 9;
                break;
            case 18:
                links = 5;
                break;
            case 19:
                links = 10;
                break;
            case 20:
                links = 11;
                break;
            case 21:
                links = 7;
                break;
            case 22:
                links = 14;
                break;
            case 23:
                links = 13;
                break;
            case 24:
                links = 15;
                break;
            }
            if (links & 1) {
                Grid *grid = menu->grid;
                GridItem *other;
                if (item->id % grid->dims->cols != 0 && (other = grid->cells[item->id - 1]) != NULL && other->type < 14) {
                    DrawCellQuadIfVisible_020d0dd4(&menu->linkImages[linkFrame], x, y, 400, 0x7fff,
                                                   data_ov075_020d1498, 0);
                }
            }
            if (links & 2) {
                Grid *grid = menu->grid;
                GridItem *other;
                if (item->id / grid->dims->cols != 0 && (other = grid->cells[item->id - grid->dims->cols]) != NULL
                    && other->type < 14) {
                    DrawCellQuadIfVisible_020d0dd4(&menu->linkImages[linkFrame], x, y, 400, 0x7fff,
                                                   data_ov075_020d148c, 0);
                }
            }
            if (links & 4) {
                Grid *grid = menu->grid;
                GridItem *other;
                if (item->id % grid->dims->cols < grid->dims->cols - 1 && (other = grid->cells[item->id + 1]) != NULL
                    && other->type < 14) {
                    DrawCellQuadIfVisible_020d0dd4(&menu->linkImages[linkFrame], x, y, 400, 0x7fff,
                                                   data_ov075_020d1488, 0);
                }
            }
            if (links & 8) {
                Grid *grid = menu->grid;
                GridItem *other;
                if (item->id / grid->dims->cols < grid->dims->rows - 1
                    && (other = grid->cells[item->id + grid->dims->cols]) != NULL && other->type < 14) {
                    DrawCellQuadIfVisible_020d0dd4(&menu->linkImages[linkFrame], x, y, 400, 0x7fff,
                                                   data_ov075_020d1490, 0);
                }
            }
        }

        if (image != NULL) {
            if (cell.width != 0) {
                DrawCellQuadIfVisible_020d0dd4(image, x, y, 400, color, cell, highlight);
            } else if (item->type >= 6) {
                DrawImageQuadWithIdIfVisible_020d0d2c(image, x, y, 400, color, item->type);
            } else {
                DrawImageQuadIfVisible_020d0cd8(image, x, y, 400, color, highlight);
            }
        } else if (node != NULL) {
            DrawNodeAtInvertedY_020d0e30(node, nodeX + (x << 12), nodeY + (y << 12));
        }
    }

    {
        u16 unlocked = data_0205fe0c->unlockMask;
        for (i = 0; i < 12; i++) {
            if (unlocked & (1 << i) & menu->trailMask) {
                PipeTrail *trail = &menu->trails[i];
                int step = trail->step;
                Point16 *point = &trail->points[step >> 3];
                if (trail->delay != 0) {
                    trail->delay--;
                } else {
                    int trailFrame = step & 7;
                    if (trail->reverse == 0) {
                        trailFrame = 7 - trailFrame;
                    }
                    DrawImageQuadIfVisible_020d0cd8(&menu->trailImages[trailFrame],
                                                    point->x * 16 + 0x80 - (menu->scrollX >> 12),
                                                    point->y * 16 + 0x58 - (menu->scrollY >> 12), 0x2c8, 0x7fff, 0);
                    if (trail->reverse) {
                        if (step != 0) {
                            trail->step--;
                        } else {
                            trail->reverse = 0;
                            trail->step = 0;
                            trail->delay = 15;
                        }
                    } else if (step < trail->length) {
                        trail->step++;
                    } else {
                        trail->reverse = 1;
                        trail->step = trail->length;
                        trail->delay = 15;
                    }
                }
            }
        }
    }
}
