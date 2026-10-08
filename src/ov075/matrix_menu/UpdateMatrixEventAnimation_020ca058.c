#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MatrixNode {
    u16 index;
    u8 type;
    s8 requiredFlag;
    s16 lockValue;
    u16 bitIndex;
    u8 pendingSteps;
    u8 visited;
    u8 pad_0a[2];
    s16 links[4];
} MatrixNode;

typedef struct {
    u8 pad_0000[4];
    u16 groupCells[10];
    MatrixNode *firstNode;
    u8 pad_001c[0x98 - 0x1c];
    u8 *columns;
    MatrixNode *nodes[(0x24dc - 0x9c) / 4];
    s16 groupValues[1];
} MatrixMap;

typedef struct {
    u8 pad_000[0xa4];
    fx32 x;
    fx32 y;
    u8 pad_0ac[0x104 - 0xac];
} SceneNode;

typedef struct {
    u32 words[6];
} RefreshArgs;

typedef struct {
    u8 first;
    u8 second;
} GroupPair;

typedef struct {
    u8 pad_0000[0x2c58];
    u32 portalMask;
    int clearedBits[1];
    u8 pad_2c60[0x2c68 - 0x2c60];
    u8 keyCount;
    u8 pad_2c69;
    u8 crownCount;
} SaveData;

typedef struct {
    u8 pad_00[0x28];
    int messageArg;
} SlotEntry;

typedef struct {
    u8 pad_00000[7];
    u8 needsRedraw;
    u8 pad_00008[0x2c - 0x8];
    int busy;
    s16 focusX;
    s16 focusY;
    u8 pad_00034[0x68 - 0x34];
    int revealActive;
    int revealDone;
    u8 pad_00070[0x4ee0 - 0x70];
    int messageBank[4];
    u8 pad_04ef0[0x11fac - 0x4ef0];
    void *currentMessage;
    u8 pad_11fb0[0x12dd0 - 0x11fb0];
    MatrixMap *map;
    MatrixNode *current;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    void *layout;
    u8 pad_131a8[0x13464 - 0x131a8];
    SceneNode portalEffect1;
    SceneNode portalEffect2;
    u8 pad_1366c[0x13678 - 0x1366c];
    SceneNode portalEffect3;
    SceneNode portalEffect4;
    u8 pad_13880[0x138ec - 0x13880];
    SceneNode *cursor;
    SceneNode effects[5];
    u8 pad_13e04[0x13e64 - 0x13e04];
    u16 state;
    s16 eventParam;
    MatrixNode *pendingNode;
    MatrixNode *eventNode;
    MatrixNode *lastNode;
    u32 timer;
    int phase;
    u8 pad_13e7c[0x13ee0 - 0x13e7c];
    u8 revealState[0x1751c - 0x13ee0];
    int bonusPending;
    u8 pad_17520[0x178a4 - 0x17520];
    u32 groupMask;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern const RefreshArgs data_ov075_020d1500;
extern const GroupPair data_ov075_020d141c[];

extern BOOL AdvanceAnimationTracks_0202ef24(SceneNode *node, fx32 delta);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern void func_01ffb2f8(void *effect, int kind, int arg);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void SetPackedBit(int *bitWords, int bitIndex);
extern SlotEntry *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern void *func_ov027_020ba2a8(int *bank, int index);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void SetScreenBrightness_020bc648(int brightness);
extern void func_ov073_020c1eb4(SaveData *save, const RefreshArgs *args);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern u32 PropagateMatrixNodeVisit_020c5778(MatrixMenu *menu, MatrixNode *node, int dir, BOOL quiet, BOOL keepSteps);
extern void func_ov075_020c5d10(MatrixMenu *menu, int a, int b, int c);
extern BOOL TryCompleteGridGroup_020c5fac(MatrixMenu *menu, u32 group);
extern void func_ov075_020c7fa8(void *state, MatrixMap *map, MatrixNode *node, int index);
extern void ClearGlyphCell_020c8870(void *pixels, MatrixMap *grid, u32 cellIndex);
extern void ShowDialogMessage_020c8ce4(MatrixMenu *menu, int messageId, int dialogType, int cancelable, ...);
extern void GetGridCellPosition_020ca00c(MatrixMenu *menu, MatrixNode *cell, fx32 *x, fx32 *y);
extern void SetUnlockableElementsVisible_020d0e64(void *layout, BOOL visible);
extern void func_ov075_020caf38(MatrixMenu *menu);
extern void func_ov075_020cb178(MatrixMenu *menu);
extern void func_ov075_020cb410(MatrixMenu *menu);
extern void func_ov075_020cb658(MatrixMenu *menu);

static inline void RefreshRevealedCell(MatrixMenu *menu, MatrixNode *cell)
{
    if (cell->type >= 0xe) {
        cell->pendingSteps = 0;
        func_ov075_020c7fa8(menu->revealState, menu->map, cell, cell->index);
    }
}

static inline void MarkPortalCleared(int bit)
{
    RefreshArgs args = data_ov075_020d1500;
    data_0205fe0c->portalMask |= 1 << bit;
    func_ov073_020c1eb4(data_0205fe0c, &args);
}

static inline MatrixNode *GetGroupNode(MatrixMap *map, int group)
{
    return map->nodes[map->groupCells[group]];
}

static inline BOOL UpdateGroupReveal(MatrixMenu *menu)
{
    MatrixNode *cell;
    int columns;
    fx32 x;
    fx32 y;

    switch (menu->phase) {
    case 0:
        cell = GetGroupNode(menu->map, data_ov075_020d141c[menu->eventParam].first);
        columns = *menu->map->columns;
        menu->focusX = (cell->index % columns) * 16 + 0x18;
        menu->focusY = (cell->index / columns) * 16 + 0x18;
        menu->phase++;
        menu->timer = 0;
        break;
    case 1:
        if (menu->busy != 0) {
            break;
        }
        if (AdvanceAnimationTracks_0202ef24(&menu->effects[4], 0x1000) == 0) {
            GetGridCellPosition_020ca00c(menu, GetGroupNode(menu->map, data_ov075_020d141c[menu->eventParam].first), &x, &y);
            menu->effects[4].x = x + 0x18000;
            menu->effects[4].y = y - 0x18000;
            SceneNode_Draw_01ffb12c(&menu->effects[4]);
            if (++menu->timer == 4) {
                PlaySoundEffect_0204d924(1, 0xb);
            }
        } else {
            cell = GetGroupNode(menu->map, data_ov075_020d141c[menu->eventParam].second);
            columns = *menu->map->columns;
            menu->focusX = (cell->index % columns) * 16 + 0x18;
            menu->focusY = (cell->index / columns) * 16 + 0x18;
            menu->phase++;
            menu->timer = 0;
        }
        break;
    case 2:
        if (menu->busy != 0) {
            break;
        }
        if (AdvanceAnimationTracks_0202ef24(&menu->effects[4], 0x1000) == 0) {
            GetGridCellPosition_020ca00c(menu, GetGroupNode(menu->map, data_ov075_020d141c[menu->eventParam].second), &x, &y);
            menu->effects[4].x = x + 0x18000;
            menu->effects[4].y = y - 0x18000;
            SceneNode_Draw_01ffb12c(&menu->effects[4]);
            if (++menu->timer == 4) {
                menu->groupMask = -1;
                PlaySoundEffect_0204d924(1, 0xb);
            }
        } else {
            return FALSE;
        }
        break;
    }
    return TRUE;
}

void UpdateMatrixEventAnimation_020ca058(MatrixMenu *menu)
{
    u16 state;
    int high;
    MatrixNode *target;
    fx32 x;
    fx32 y;
    fx32 targetX;
    fx32 targetY;
    MatrixNode *node;
    MatrixNode **nodes;
    s16 *link;
    s16 remaining;
    BOOL anyOpen;
    BOOL open;
    MatrixNode *child;
    BOOL completed;
    int columns;
    MatrixNode *cell0;
    int nearColumns;
    int next;
    MatrixNode *cell2;
    MatrixNode *cell1;
    MatrixNode *cell3;
    int index;
    s16 i;
    void *effect;
    SlotEntry *entry;
    MatrixMap *map;

    state = menu->state;
    if (state != 0) {
        if ((state & 0xff) != 0) {
            GetGridCellPosition_020ca00c(menu, (state & 0xff) == 1 ? menu->pendingNode : menu->current, &x, &y);
            if ((menu->state & 0xff) == 1) {
                if (AdvanceAnimationTracks_0202ef24(menu->cursor, 0x1000) == 0) {
                    menu->cursor->x = x + 0x9000;
                    menu->cursor->y = y - 0x8000;
                    SceneNode_Draw_01ffb12c(menu->cursor);
                    if (++menu->timer == 4) {
                        PlaySoundEffect_0204d924(1, 5);
                    }
                } else {
                    menu->state = 0;
                    menu->timer = 0;
                    PropagateMatrixNodeVisit_020c5778(menu, menu->pendingNode, 4, FALSE, FALSE);
                    if (menu->eventParam >= 0 && menu->state == 0 && TryCompleteGridGroup_020c5fac(menu, menu->eventParam)) {
                        menu->state = 0x500;
                        func_01ffb2f8(&menu->effects[4], 2, 0);
                        func_01ffb2f8(&menu->effects[4], 4, 0);
                        func_01ffb2f8(&menu->effects[4], 0, 0);
                        func_ov075_020c5d10(menu, -1, -1, 0);
                        menu->groupMask ^= 1 << menu->eventParam;
                        menu->phase = 0;
                    }
                    if (menu->state == 0) {
                        menu->currentMessage = func_ov027_020ba2a8(menu->messageBank, 0x58);
                        menu->needsRedraw = 1;
                        SetSecondaryElementEnabled_020bc084(TRUE);
                        SetUnlockableElementsVisible_020d0e64(menu->layout, TRUE);
                    }
                    return;
                }
            }
        }

        high = menu->state & ~0xff;
        if (high != 0) {
            if (high != 0x500) {
                target = high != 0x100 ? menu->eventNode : menu->current;
                GetGridCellPosition_020ca00c(menu, target, &targetX, &targetY);
                menu->lastNode = target;
            }

            switch (high) {
            case 0x100:
                if (AdvanceAnimationTracks_0202ef24(&menu->effects[0], 0x1000) == 0) {
                    menu->effects[0].x = targetX + 0x11000;
                    menu->effects[0].y = targetY - 0x10000;
                    SceneNode_Draw_01ffb12c(&menu->effects[0]);
                    if (++menu->timer == 2) {
                        PlaySoundEffect_0204d924(1, 8);
                    }
                    if (menu->timer == 7) {
                        node = menu->current;
                        SetPackedBit(data_0205fe0c->clearedBits, node >= menu->map->firstNode ? node - menu->map->firstNode : -1);
                    }
                    break;
                }
                menu->state &= 0xff;
                anyOpen = FALSE;
                menu->timer = 0;
                node = menu->current;
                nodes = menu->map->nodes;
                remaining = 4;
                menu->revealDone = 0;
                menu->revealActive = 1;
                link = node->links;
                if (node->links[1] >= 0) {
                    func_ov075_020caf38(menu);
                } else if (node->links[2] >= 0) {
                    func_ov075_020cb658(menu);
                } else if (node->links[0] >= 0) {
                    func_ov075_020cb410(menu);
                } else if (node->links[3] >= 0) {
                    func_ov075_020cb178(menu);
                }
                open = FALSE;
                if (link[0] >= 0 && nodes[link[0]]->lockValue >= 0) {
                    open = TRUE;
                }
                anyOpen |= open;
                open = FALSE;
                if (link[1] >= 0 && nodes[link[1]]->lockValue >= 0) {
                    open = TRUE;
                }
                anyOpen |= open;
                open = FALSE;
                if (link[2] >= 0 && nodes[link[2]]->lockValue >= 0) {
                    open = TRUE;
                }
                anyOpen |= open;
                open = FALSE;
                if (link[3] >= 0 && nodes[link[3]]->lockValue >= 0) {
                    open = TRUE;
                }
                anyOpen |= open;
                if (anyOpen) {
                    for (i = 0; i < 4; i++) {
                        if (link[i] >= 0) {
                            nodes[link[i]]->visited = 1;
                        }
                    }
                }
                menu->revealDone = 1;
                do {
                    if (*link >= 0) {
                        child = nodes[*link];
                        completed = FALSE;
                        if (child->type == 1 && TryCompleteGridGroup_020c5fac(menu, child->bitIndex)) {
                            menu->state |= 0x500;
                            func_01ffb2f8(&menu->effects[4], 2, 0);
                            func_01ffb2f8(&menu->effects[4], 4, 0);
                            func_01ffb2f8(&menu->effects[4], 0, 0);
                            menu->eventParam = child->bitIndex;
                            menu->groupMask ^= 1 << menu->eventParam;
                            menu->phase = 0;
                            completed = TRUE;
                        } else {
                            SetSecondaryElementEnabled_020bc084(TRUE);
                        }
                        if (anyOpen) {
                            nearColumns = *menu->map->columns;
                            RefreshRevealedCell(menu, nodes[node->index]);
                            RefreshRevealedCell(menu, nodes[node->index + 1]);
                            RefreshRevealedCell(menu, nodes[node->index + nearColumns]);
                            RefreshRevealedCell(menu, nodes[node->index + nearColumns + 1]);
                            anyOpen = FALSE;
                        }
                        if (completed) {
                            func_ov075_020c5d10(menu, -1, -1, 0);
                            break;
                        }
                    }
                    link++;
                } while (--remaining > 0);
                if (remaining == 0) {
                    menu->currentMessage = func_ov027_020ba2a8(menu->messageBank, 0x58);
                    menu->needsRedraw = 1;
                }
                index = node->index;
                columns = *menu->map->columns;
                cell0 = nodes[index];
                ClearGlyphCell_020c8870(menu->revealState, menu->map, index);
                func_ov075_020c7fa8(menu->revealState, menu->map, cell0, index);
                next = index + 1;
                cell1 = nodes[next];
                ClearGlyphCell_020c8870(menu->revealState, menu->map, next);
                func_ov075_020c7fa8(menu->revealState, menu->map, cell1, next);
                cell2 = nodes[index + columns];
                ClearGlyphCell_020c8870(menu->revealState, menu->map, index + columns);
                func_ov075_020c7fa8(menu->revealState, menu->map, cell2, index + columns);
                cell3 = nodes[index + columns + 1];
                ClearGlyphCell_020c8870(menu->revealState, menu->map, index + columns + 1);
                func_ov075_020c7fa8(menu->revealState, menu->map, cell3, index + columns + 1);
                break;
            case 0x200:
                if (AdvanceAnimationTracks_0202ef24(&menu->effects[1], 0x1000) == 0) {
                    menu->effects[1].x = targetX + 0x11000;
                    menu->effects[1].y = targetY - 0x10000;
                    SceneNode_Draw_01ffb12c(&menu->effects[1]);
                    if (++menu->timer == 4) {
                        PlaySoundEffect_0204d924(1, 0xb);
                    }
                    break;
                }
                map = menu->map;
                entry = GetRecordSlotPair1Entry_02051ef4(target->type == 6 ? map->groupValues[target->bitIndex] : -1);
                menu->state &= 0xff;
                menu->timer = 0;
                MarkPortalCleared(target->bitIndex);
                SetStatusPageAndCursor_020c2ca4(2, *(int *)entry);
                ShowDialogMessage_020c8ce4(menu, 0x20, 0, 0, entry->messageArg);
                break;
            case 0x300:
                if (AdvanceAnimationTracks_0202ef24(&menu->effects[2], 0x1000) == 0) {
                    menu->effects[2].x = targetX + 0x19000;
                    menu->effects[2].y = targetY - 0x18000;
                    SceneNode_Draw_01ffb12c(&menu->effects[2]);
                    if (++menu->timer == 4) {
                        PlaySoundEffect_0204d924(1, 0xb);
                    }
                    break;
                }
                menu->state &= 0xff;
                menu->timer = 0;
                ShowDialogMessage_020c8ce4(menu, 0x22, 0, 0, data_0205fe0c->crownCount + 1);
                break;
            case 0x400:
                if (AdvanceAnimationTracks_0202ef24(&menu->effects[3], 0x1000) == 0) {
                    menu->effects[3].x = targetX + 0x21000;
                    menu->effects[3].y = targetY - 0x10000;
                    SceneNode_Draw_01ffb12c(&menu->effects[3]);
                    if (++menu->timer == 4) {
                        PlaySoundEffect_0204d924(1, 0xb);
                    }
                    break;
                }
                menu->state &= 0xff;
                menu->timer = 0;
                func_ov073_020c1eb4(data_0205fe0c, NULL);
                SetStatusPageAndCursor_020c2ca4(1, data_0205fe0c->keyCount + 2);
                ShowDialogMessage_020c8ce4(menu, 0x21, 0, 0, data_0205fe0c->keyCount + 3);
                break;
            case 0x500:
                if (!UpdateGroupReveal(menu)) {
                    menu->groupMask = -1;
                    menu->state &= 0xff;
                    menu->timer = 0;
                    menu->phase = 0;
                    ShowDialogMessage_020c8ce4(menu, 0x2b, 0, 0);
                }
                break;
            case 0x600:
                if (menu->timer <= 0x10) {
                    SetScreenBrightness_020bc648(menu->timer);
                    if (menu->timer == 0x10) {
                        effect = NULL;
                        switch (menu->eventParam) {
                        case 1:
                            effect = &menu->portalEffect1;
                            break;
                        case 2:
                            effect = &menu->portalEffect2;
                            break;
                        case 3:
                            effect = &menu->portalEffect3;
                            break;
                        case 4:
                            effect = &menu->portalEffect4;
                            break;
                        }
                        func_01ffb2f8(effect, 2, 0x1000);
                    }
                } else if (menu->timer <= 0x20) {
                    SetScreenBrightness_020bc648(0x20 - menu->timer);
                }
                if (menu->timer == 0x20) {
                    menu->state &= 0xff;
                    menu->timer = 0;
                    menu->bonusPending = 1;
                    ShowDialogMessage_020c8ce4(menu, menu->eventParam + 0x2c, 0, 0);
                } else {
                    menu->timer++;
                }
                break;
            }
        }
    }
}
