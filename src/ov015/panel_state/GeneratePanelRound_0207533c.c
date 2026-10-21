#include "nitro/types.h"

typedef struct {
    s8 value;
    s8 weight;
} WeightedEntry;

typedef struct {
    s8 kind;
    s8 slotCount;
    s8 requiredCount;
    s8 minimumCount;
    s8 baseCount;
    s8 extraCount;
    s8 hasPartner;
} RoundConfig;

typedef struct {
    s8 lowGroup;
    s8 highGroup;
    u8 pad_02[2];
    RoundConfig configs[3];
} GroupRange;

typedef struct {
    u8 pad_00[2];
    u8 isSpecial;
    u8 textId;
} GroupInfo;

typedef struct {
    s16 level;
    u16 flags;
    s16 group;
    u8 pad_06[6];
    int linkA;
    int linkB;
    int linkC;
} PanelSlot;

typedef struct {
    u8 pad_00[0x20];
    s16 cursorA;
    s16 cursorB;
    u8 pad_24[0x3a - 0x24];
    u16 partnerName[0x50 - 0x3a >> 1];
    s8 rangeIndex;
    s8 partnerGroup;
    s8 resultKind;
    s8 targetGroup;
    s8 kind;
    s8 slotCount;
    u8 pad_56;
    s8 requiredCount;
    s8 minimumCount;
    s8 lockedCount;
    u8 pad_5a;
    s8 markA;
    s8 bonusSlot;
    u8 pad_5d[0x64 - 0x5d];
    int scale;
    int baseScale;
    int selectedA;
    u8 pad_70[8];
    int selectedB;
    u8 pad_7c[8];
    PanelSlot slots[9];
    u8 pad_15c_fill[0x15c - 0x84 - 9 * 0x18];
    RoundConfig *config;
} PanelState;

typedef struct {
    u8 pad_00[0xc];
    u32 pad_bits : 20;
    u32 partnerRank : 5;
    u32 pad_hi : 7;
    u16 name[11];
} PartnerInfo;

extern PanelState *data_ov015_020812e0;
extern WeightedEntry data_ov015_0207a1e0[];
extern WeightedEntry data_ov015_0207a218[];
extern GroupRange data_ov015_0207a310[];
extern GroupInfo data_ov015_0207a40c[];
extern u8 data_ov015_0207a548[];
extern WeightedEntry data_ov015_0207a54c[];
extern unsigned int func_0202a9d0(u16 range);
extern int PickWeightedEntry_020788a8(const WeightedEntry *entries, int count);
extern u16 *CopyWideStringBounded_020663d0(u16 *dst, const u16 *src, int maxLength);
extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);

void GeneratePanelRound_0207533c(int isFixed, int progress, u8 *partner) {
    WeightedEntry choices[3];
    PanelSlot *slots;
    PanelSlot *slot;
    WeightedEntry *table;
    GroupRange *range;
    RoundConfig *configs;
    int count;
    int i;
    int j;
    int freeGroups;
    u32 low;
    int high;
    int span;
    int locked;
    int extra;
    int pick;
    int value;
    int seen;
    int chance;
    int level;
    u8 *chances;
    WeightedEntry *specials;

    data_ov015_020812e0->cursorA = -1;
    data_ov015_020812e0->cursorB = -1;
    for (i = 0; i < 9; i++) {
        data_ov015_020812e0->slots[i].linkA = -1;
        data_ov015_020812e0->slots[i].linkB = -1;
        data_ov015_020812e0->slots[i].linkC = -1;
    }
    data_ov015_020812e0->baseScale = 0x1000;
    data_ov015_020812e0->scale = data_ov015_020812e0->baseScale;
    data_ov015_020812e0->selectedA = -1;
    data_ov015_020812e0->selectedB = -1;
    data_ov015_020812e0->markA = -1;
    data_ov015_020812e0->bonusSlot = -1;
    if (isFixed != 0) {
        table = data_ov015_0207a1e0;
        pick = PickWeightedEntry_020788a8(table, 4);
        data_ov015_020812e0->rangeIndex = table[pick].value;
    } else {
        table = data_ov015_0207a218;
        count = partner[0x6b] + 1;
        if (count > 10) {
            count = 10;
        }
        pick = PickWeightedEntry_020788a8(table, count);
        data_ov015_020812e0->rangeIndex = table[pick].value;
    }
    freeGroups = 0;
    slots = data_ov015_020812e0->slots;
    range = &data_ov015_0207a310[data_ov015_020812e0->rangeIndex];
    low = range->lowGroup;
    high = range->highGroup;
    configs = range->configs;
    span = high - low;
    for (i = 0; i < 3; i++) {
        if (configs[i].kind == 0) {
            break;
        }
    }
    data_ov015_020812e0->config = &configs[func_0202a9d0(i)];
    locked = data_ov015_020812e0->config->baseCount;
    extra = data_ov015_020812e0->config->extraCount;
    if (extra > 0) {
        locked += func_0202a9d0(extra + 1);
    }
    data_ov015_020812e0->kind = data_ov015_020812e0->config->kind;
    data_ov015_020812e0->slotCount = data_ov015_020812e0->config->slotCount;
    data_ov015_020812e0->requiredCount = data_ov015_020812e0->config->requiredCount;
    data_ov015_020812e0->minimumCount = data_ov015_020812e0->config->minimumCount;
    data_ov015_020812e0->lockedCount = locked;
    for (i = low; i < high; i++) {
        if (data_ov015_0207a40c[i].isSpecial == 0) {
            freeGroups++;
        }
    }
    data_ov015_020812e0->targetGroup = low + func_0202a9d0(freeGroups);
    for (i = 0; i < data_ov015_020812e0->slotCount; i++) {
        do {
            value = low + func_0202a9d0(span);
        } while (data_ov015_020812e0->targetGroup == value);
        slots[i].group = value;
    }
    if (data_ov015_020812e0->kind == 4) {
        for (i = low; i < high; i++) {
            do {
                slot = &slots[func_0202a9d0(data_ov015_020812e0->slotCount)];
            } while (slot->flags & 0x100);
            slot->flags |= 0x100;
            slot->group = i;
        }
    } else {
        for (i = 0; i < locked; i++) {
            do {
                slot = &slots[func_0202a9d0(data_ov015_020812e0->slotCount)];
            } while (data_ov015_020812e0->targetGroup == slot->group);
            slot->group = data_ov015_020812e0->targetGroup;
        }
    }
    if (data_ov015_020812e0->config->hasPartner != 0) {
        PartnerInfo *info = (PartnerInfo *)partner;
        int rank = info->partnerRank;
        if (rank != 0) {
            data_ov015_020812e0->resultKind = 5;
            data_ov015_020812e0->partnerGroup = rank + 0x3c;
            CopyWideStringBounded_020663d0(data_ov015_020812e0->partnerName, info->name, 10);
        } else {
            data_ov015_020812e0->resultKind = 6;
            do {
                data_ov015_020812e0->partnerGroup = low + func_0202a9d0(freeGroups);
            } while (data_ov015_020812e0->targetGroup == data_ov015_020812e0->partnerGroup);
            for (i = 0; i < data_ov015_020812e0->slotCount; i++) {
                slot = &slots[i];
                if (data_ov015_020812e0->partnerGroup == slot->group) {
                    do {
                        value = low + func_0202a9d0(span);
                    } while (data_ov015_020812e0->targetGroup == value || data_ov015_020812e0->partnerGroup == value);
                    slot->group = value;
                }
            }
        }
        if (data_ov015_020812e0->resultKind == 5 || data_ov015_020812e0->resultKind == 6) {
            pick = func_0202a9d0(data_ov015_020812e0->slotCount - locked);
            value = 0;
            for (i = 0; i < data_ov015_020812e0->slotCount; i++) {
                slot = &slots[i];
                if (data_ov015_020812e0->targetGroup != slot->group) {
                    if (pick == value) {
                        slot->group = data_ov015_020812e0->partnerGroup;
                        break;
                    }
                    value++;
                }
            }
        }
    }
    if (data_ov015_020812e0->kind == 4) {
        return;
    }
    chances = data_ov015_0207a548;
    specials = data_ov015_0207a54c;
    if (progress <= 0x31) {
        j = 0;
    } else {
        j = 1;
        if (progress > 0x4f) {
            j = 2;
        }
    }
    locked = chances[j];
    level = (s8)DispatchContextCommand_02066c78(0x11, 0, 0, 0);
    for (i = 0; i < data_ov015_020812e0->slotCount; i++) {
        slot = &slots[i];
        if (data_ov015_020812e0->targetGroup == slot->group || data_ov015_020812e0->partnerGroup == slot->group) {
            continue;
        }
        if ((int)func_0202a9d0(100) >= locked) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            choices[j] = specials[j];
            if (choices[j].value == 0x3b && level >= 0x63) {
                choices[j].weight = 0;
            }
        }
        value = choices[PickWeightedEntry_020788a8(choices, 3)].value;
        count = data_ov015_020812e0->slotCount;
        for (pick = 0; pick < data_ov015_020812e0->slotCount; pick++) {
            if (value == slots[pick].group) {
                break;
            }
        }
        if (pick < count) {
            continue;
        }
        switch (value) {
        case 0x3a:
            if (data_ov015_020812e0->kind == 3) {
                if (data_ov015_020812e0->requiredCount >= count - data_ov015_020812e0->lockedCount) {
                    continue;
                }
            } else if (data_ov015_020812e0->requiredCount >= count) {
                continue;
            }
            break;
        case 0x3b:
            if (level >= 0x63) {
                continue;
            }
            break;
        case 0x3c:
            data_ov015_020812e0->bonusSlot = i;
            break;
        default:
            continue;
        }
        slot->group = value;
    }
}
