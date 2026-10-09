#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0xc];
    int id;
} Widget;

typedef struct WidgetPos {
    int x;
    int y;
} WidgetPos;

typedef struct ResultsParams {
    s32 earnedAmount;
    s32 bonusAmount;
    u8 pad_08[0x1a];
    u8 worldId;
    u8 pad_23;
    u8 unlockedRank;
    u8 maxRank;
    u8 pad_26[0x66];
    s32 isBonusStage;
} ResultsParams;

typedef struct ResultsWork {
    u8 pad_0000[6];
    u16 flags;
    u8 pad_0008[0x54];
    u8 widgets[0x6b54];
    s32 timer;
    u8 pad_6bb4[4];
    s32 busy;
    s32 multipliers[3];
    s32 mode;
    s32 prevMode;
    s32 shopOpen;
    u8 pad_6bd4[4];
    s32 popupTimer;
    s32 outcome;
    s32 shownBase;
    s32 shownTotal;
    s32 shownTicks;
    u8 pad_6bec[0xc];
    s32 menuIndex;
    u8 pad_6bfc[0x164];
    u16 *ownedFlags;
    s32 entryCount;
    s32 shopBase;
    s32 rateA;
    s32 rateB;
    s32 selected;
    s32 cursor;
    s32 scroll;
    u8 pad_6d80[4];
    s32 tab;
    s32 confirmChoice;
    u8 pad_6d8c[4];
    s32 sessionKind;
    s32 jinglePlaying;
} ResultsWork;

typedef struct ResultsScreen {
    ResultsParams *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct ShopItem {
    s16 itemId;
    u8 level;
    u8 kind;
} ShopItem;

typedef struct ShopEntry {
    ShopItem item;
    s32 price;
    s8 unique;
    s8 requiredRank;
    u8 pad_0a[2];
} ShopEntry;

typedef struct SessionState {
    u8 pad_00[6];
    u16 mode : 3;
    u16 rest : 13;
    u8 pad_08[3];
    u8 rank;
    u32 seed;
} SessionState;

typedef struct SaveData {
    u8 pad_0000[0x28cc];
    u32 munny;
    s32 points;
} SaveData;

extern ResultsScreen data_ov034_020c0fa0;
extern ShopEntry gResultsShopEntries[];
extern u16 data_02060500;
extern SessionState data_0206085c;
extern SaveData *data_0205fe0c;

extern Widget *FindWidgetById(void *root, int id);
extern void SetFocusedWidget(void *root, Widget *widget);
extern void ApplyWidgetFocusAnims(void *root, Widget *widget, BOOL focused);
extern void SetEntrySlotsVisible(void *root, Widget *widget, int visible);
extern void func_ov027_020b9380(void *root, Widget *widget, WidgetPos *pos, int mode);
extern void func_ov027_020b91e8(void *root, Widget *widget, WidgetPos *pos, int mode);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void StopSeqArcOrDefault(int seqArcNo, int player, int fadeFrames);
extern void SetSecondaryBrightness(int value);
extern unsigned int func_0202a9e4(unsigned int range);
extern unsigned int random_next_scaled(unsigned int upperBound);
extern int func_ov001_02064a38(ShopItem *item, int notify);
extern void SetResultsMode(u32 mode);
extern void EnterResultsTierMode(u32 mode);
extern void CommitResultsRewards(void);
extern BOOL IsResultsShopEntryUnlocked(int index);
extern void MarkResultsComplete(int unused);
extern void SetupStageParams(ResultsParams *params, int stage, int level);
extern u32 ClassifyResultsShopEntry(int index);

#define WORK (data_ov034_020c0fa0.work)
#define PARAMS (data_ov034_020c0fa0.params)

void HandleResultsInput(Widget *widget, u32 pressed)
{
    WidgetPos pos;
    ShopItem item;
    int sessionKind;
    int id;

    if (WORK->flags & 0x4000) {
        return;
    }
    if (WORK->outcome != -1) {
        return;
    }
    if (WORK->mode == 4 && (WORK->busy != 0 || WORK->menuIndex == 0)) {
        ResultsWork *focusWork = *(ResultsWork *volatile *)&WORK;
        SetFocusedWidget(WORK->widgets, FindWidgetById(focusWork->widgets, focusWork->confirmChoice + 0xe0));
        return;
    }
    if (WORK->popupTimer > 0) {
        if (!(data_02060500 & 1)) {
            return;
        }
        WORK->popupTimer = 0;
        WORK->menuIndex = 0;
        WORK->timer = 0;
        PlaySoundEffect(0, 1);
        return;
    }
    if (WORK->mode == 3) {
        if (WORK->entryCount > 6) {
            if ((pressed & 0x40) && widget->id == 0xd5 && WORK->cursor == 0) {
                if (WORK->scroll > 0) {
                    WORK->scroll = WORK->scroll - 1;
                } else {
                    widget = FindWidgetById(WORK->widgets, 0xda);
                    SetFocusedWidget(WORK->widgets, widget);
                    WORK->scroll = WORK->entryCount - 6;
                }
            }
            if ((pressed & 0x80) && widget->id == 0xda && WORK->cursor == 5) {
                if (WORK->entryCount > WORK->scroll + 6) {
                    WORK->scroll = WORK->scroll + 1;
                } else {
                    widget = FindWidgetById(WORK->widgets, 0xd5);
                    SetFocusedWidget(WORK->widgets, widget);
                    WORK->scroll = 0;
                }
            }
            if (pressed & 0x20) {
                int next;
                if (WORK->scroll == 0) {
                    widget = FindWidgetById(WORK->widgets, 0xd5);
                    SetFocusedWidget(WORK->widgets, widget);
                }
                next = WORK->scroll - 6;
                if (next < 0) {
                    next = 0;
                }
                WORK->scroll = next;
            }
            if (pressed & 0x10) {
                int limit;
                int next;
                if (WORK->scroll == WORK->entryCount - 6) {
                    widget = FindWidgetById(WORK->widgets, 0xda);
                    SetFocusedWidget(WORK->widgets, widget);
                }
                limit = WORK->entryCount - 6;
                next = WORK->scroll + 6;
                if (next > limit) {
                    next = limit;
                }
                WORK->scroll = next;
            }
            if (WORK->shopOpen != 0 && (data_02060500 & 2)) {
                widget = FindWidgetById(WORK->widgets, 0xd9);
                SetFocusedWidget(WORK->widgets, widget);
                WORK->scroll = WORK->entryCount - 6;
            }
        } else {
            if (((pressed & 0x40) && widget->id == 0xd5 && WORK->cursor == 0) || (pressed & 0x10)) {
                widget = FindWidgetById(WORK->widgets, WORK->entryCount + 0xd4);
                SetFocusedWidget(WORK->widgets, widget);
            }
            if (((pressed & 0x80) && widget->id == WORK->entryCount + 0xd4 && WORK->cursor == WORK->entryCount - 1) ||
                (pressed & 0x20)) {
                widget = FindWidgetById(WORK->widgets, 0xd5);
                SetFocusedWidget(WORK->widgets, widget);
            }
            if (WORK->shopOpen != 0 && (data_02060500 & 2)) {
                widget = FindWidgetById(WORK->widgets, WORK->entryCount + 0xd3);
                SetFocusedWidget(WORK->widgets, widget);
            }
        }
    }
    func_ov027_020b9380(WORK->widgets, widget, &pos, 0);
    id = widget->id;
    if ((id >= 0x12 && id <= 0x14 && WORK->tab != id - 0x12) ||
        (id >= 0x74 && id <= 0x75 && WORK->tab != id - 0x74) ||
        (id >= 0xd5 && id <= 0xda && WORK->selected != id - 0xd5 + WORK->scroll) ||
        (id >= 0xe0 && id <= 0xe1 && WORK->confirmChoice != id - 0xe0)) {
        PlaySoundEffect(0, 0);
    }
    id = widget->id;
    if (id >= 0x12 && id <= 0x14) {
        WORK->tab = id - 0x12;
        func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 10), &pos, 0);
    }
    if (widget->id == 0x19) {
        func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 10), &pos, 0);
    }
    id = widget->id;
    if (id >= 0x74 && id <= 0x75) {
        WORK->tab = id - 0x74;
        func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 100), &pos, 0);
    }
    id = widget->id;
    if (id >= 0xd5 && id <= 0xda) {
        WORK->cursor = id - 0xd5;
        WORK->selected = WORK->cursor + WORK->scroll;
        func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 200), &pos, 0);
    }
    id = widget->id;
    if (id >= 0xe0 && id <= 0xe1) {
        WORK->confirmChoice = id - 0xe0;
        func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 0xe2), &pos, 0);
    }
    sessionKind = WORK->sessionKind;
    if (sessionKind == 1 && data_0206085c.mode == 1) {
        if (!(data_02060500 & 0x402)) {
            return;
        }
        if (WORK->busy != 0) {
            return;
        }
        WORK->outcome = 0;
        WORK->timer = 0;
        PlaySoundEffect(0x19b, 1);
        return;
    }
    if ((data_02060500 & 0x400) && WORK->mode >= 0 && WORK->mode <= 2 && !(WORK->flags & 0x4000)) {
        WORK->prevMode = WORK->mode;
        SetResultsMode(3);
        WORK->menuIndex = 0;
        PlaySoundEffect(0, 2);
        return;
    }
    if ((data_02060500 & 0x402) && WORK->mode == 3 && WORK->prevMode >= 0) {
        SetResultsMode(WORK->prevMode);
        WORK->menuIndex = -1;
        WORK->prevMode = -1;
        PlaySoundEffect(0, 3);
        return;
    }
    if (data_02060500 & 1) {
        switch (WORK->mode) {
        case 0:
            WORK->mode = 1;
            SetFocusedWidget(WORK->widgets, FindWidgetById(WORK->widgets, 0x19));
            ApplyWidgetFocusAnims(WORK->widgets, widget, TRUE);
            func_ov027_020b9380(WORK->widgets, FindWidgetById(WORK->widgets, 0x19), &pos, 0);
            func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 10), &pos, 0);
            PARAMS->bonusAmount = PARAMS->earnedAmount * WORK->multipliers[WORK->tab] / 100;
            WORK->shownTotal = PARAMS->earnedAmount - PARAMS->bonusAmount;
            WORK->shownTicks = (WORK->shownTotal - WORK->shownBase) / 10;
            PlaySoundEffect(0, 1);
            return;
        case 1:
            if (WORK->busy == 0) {
                PARAMS->earnedAmount = PARAMS->earnedAmount - PARAMS->bonusAmount;
                MarkResultsComplete(0);
                CommitResultsRewards();
                WORK->timer = 0;
                PlaySoundEffect(0, 1);
                if (PARAMS->isBonusStage != 0) {
                    StopSeqArcOrDefault(0x19b, 0, 4);
                    WORK->jinglePlaying = 0;
                    return;
                }
            }
            break;
        case 2:
            if (WORK->tab == 0) {
                if (sessionKind == 1) {
                    WORK->outcome = 0;
                    data_0206085c.mode = 3;
                    WORK->timer = 0;
                } else {
                    PARAMS->unlockedRank++;
                    SetSecondaryBrightness(-16);
                    data_0206085c.rank = PARAMS->unlockedRank;
                    data_0206085c.seed = func_0202a9e4(0xffff) + random_next_scaled(-1);
                    SetupStageParams(PARAMS, PARAMS->worldId, PARAMS->unlockedRank);
                    EnterResultsTierMode(0);
                    WORK->timer = 2;
                }
            } else {
                if (sessionKind == 0 && PARAMS->unlockedRank != PARAMS->maxRank) {
                    SetResultsMode(5);
                    WORK->menuIndex = 0;
                    WORK->confirmChoice = 0;
                } else {
                    WORK->shopOpen = 1;
                    SetResultsMode(3);
                    WORK->menuIndex = 0;
                }
            }
            PlaySoundEffect(0, 1);
            return;
        case 3:
            if (WORK->shopOpen != 0) {
                if (ClassifyResultsShopEntry(WORK->selected) != 0 ||
                    (PARAMS->earnedAmount >= gResultsShopEntries[WORK->shopBase + WORK->selected].price &&
                     (gResultsShopEntries[WORK->shopBase + WORK->selected].unique == 0 ||
                      (WORK->selected < 0x10 && !(*WORK->ownedFlags & (1 << WORK->selected)))) &&
                     IsResultsShopEntryUnlocked(WORK->selected))) {
                    SetResultsMode(4);
                    WORK->confirmChoice = 1;
                    WORK->menuIndex = 0;
                    PlaySoundEffect(0, 1);
                } else {
                    PlaySoundEffect(0, 4);
                }
                return;
            }
            break;
        case 4:
            if (WORK->confirmChoice == 0) {
                u32 kind = ClassifyResultsShopEntry(WORK->selected);
                if (kind == 0) {
                    ShopEntry *entry = &gResultsShopEntries[WORK->shopBase + WORK->selected];
                    item.itemId = entry->item.itemId;
                    item.level = entry->item.level;
                    item.kind = entry->item.kind;
                    if (func_ov001_02064a38(&item, 0)) {
                        PARAMS->earnedAmount = PARAMS->earnedAmount - entry->price;
                        if (entry->unique != 0) {
                            if (WORK->selected < 0x10) {
                                *WORK->ownedFlags = *WORK->ownedFlags | (u16)(1 << WORK->selected);
                            }
                        } else {
                            entry->price = entry->price << 1;
                        }
                        PlaySoundEffect(0, 1);
                    } else {
                        PlaySoundEffect(0, 4);
                    }
                } else {
                    if (kind == 1) {
                        int reward = (PARAMS->earnedAmount * WORK->rateB + 99) / 100;
                        int total;
                        if (reward > 99999) {
                            reward = 99999;
                        }
                        total = data_0205fe0c->points + reward;
                        if (total < 0) {
                            total = 0;
                        } else if (total > 999999) {
                            total = 999999;
                        }
                        data_0205fe0c->points = total;
                    } else {
                        int reward = (PARAMS->earnedAmount * WORK->rateA + 99) / 100;
                        if (reward > 99999) {
                            reward = 99999;
                        }
                        data_0205fe0c->munny = data_0205fe0c->munny + reward;
                        if (data_0205fe0c->munny > 99999999) {
                            data_0205fe0c->munny = 99999999;
                        }
                    }
                    PARAMS->earnedAmount = 0;
                    if (PARAMS->unlockedRank == PARAMS->maxRank) {
                        WORK->outcome = 1;
                    } else {
                        WORK->outcome = 2;
                    }
                    if (WORK->sessionKind == 1 && data_0206085c.mode != 2) {
                        data_0206085c.mode = 4;
                    }
                    PlaySoundEffect(0, 1);
                    SetEntrySlotsVisible(WORK->widgets, FindWidgetById(WORK->widgets, 0xe2), 0);
                    SetFocusedWidget(WORK->widgets, NULL);
                }
                WORK->shownTotal = PARAMS->earnedAmount;
                WORK->shownTicks = (WORK->shownTotal - WORK->shownBase) / 10;
            } else {
                PlaySoundEffect(0, 1);
            }
            if (WORK->outcome == -1) {
                WORK->mode = 3;
                WORK->menuIndex = 0;
                return;
            }
            break;
        case 5:
            if (WORK->confirmChoice == 0) {
                WORK->shopOpen = 1;
                SetResultsMode(3);
                WORK->menuIndex = 0;
            } else {
                SetResultsMode(2);
                WORK->menuIndex = -1;
            }
            PlaySoundEffect(0, 1);
            return;
        }
    } else if (data_02060500 & 2) {
        switch (WORK->mode) {
        case 1:
            WORK->mode = 0;
            SetFocusedWidget(WORK->widgets, FindWidgetById(WORK->widgets, WORK->tab + 0x12));
            func_ov027_020b9380(WORK->widgets, FindWidgetById(WORK->widgets, WORK->tab + 0x12), &pos, 0);
            func_ov027_020b91e8(WORK->widgets, FindWidgetById(WORK->widgets, 10), &pos, 0);
            WORK->shownTotal = PARAMS->earnedAmount;
            WORK->shownTicks = PARAMS->bonusAmount / 10;
            PARAMS->bonusAmount = 0;
            PlaySoundEffect(0, 3);
            return;
        case 4:
            SetResultsMode(3);
            WORK->menuIndex = 0;
            PlaySoundEffect(0, 3);
            return;
        case 5:
            SetResultsMode(2);
            WORK->menuIndex = -1;
            PlaySoundEffect(0, 3);
            return;
        }
    }
}
