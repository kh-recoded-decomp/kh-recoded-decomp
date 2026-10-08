#include "nitro/types.h"

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
    u8 pad_0000[0x98];
    u8 *columns;
    MatrixNode *nodes[1];
    u8 pad_00a0[0x2be8 - 0xa0];
    u8 levels[1];
} MatrixMap;

typedef struct {
    int ids[4];
} NeighborIds;

typedef struct {
    u8 pad_0000[0x2c5c];
    u32 unlockBits[2];
    u8 pad_2c64[3];
    u8 currentLevel;
    u8 keyCount;
    u8 pad_2c69;
    u8 crownCount;
    u8 collectedBits;
    u8 portalBits;
    u8 pad_2c6d[0x2d38 - 0x2c6d];
    u32 clearedMask;
} SaveData;

typedef struct {
    u8 pad_00000[0x12dd0];
    MatrixMap *map;
    u8 pad_12dd4[0x139f4 - 0x12dd4];
    u8 effects[3][0x104];
    u8 pad_13d00[0x13e64 - 0x13d00];
    u16 eventFlags;
    u16 eventParam;
    u8 pad_13e68[4];
    MatrixNode *eventNode;
    u8 pad_13e70[0x13ee0 - 0x13e70];
    u8 revealState[1];
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern NeighborIds data_ov075_020d14f0;

extern int GetPackedBitMask(u32 *bitWords, int bitIndex);
extern void func_01ffb2f8(void *effect, int kind, int arg);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov075_020c7fc8(void *state, MatrixMap *map, MatrixNode *node, int index);

static inline BOOL IsNodeFlagSet(MatrixNode *node)
{
    if (GetPackedBitMask(data_0205fe0c->unlockBits, node->requiredFlag)) {
        return TRUE;
    }
    return FALSE;
}

static inline MatrixNode *GetNode(MatrixMenu *menu, int id)
{
    return menu->map->nodes[id];
}

u32 PropagateMatrixNodeVisit(MatrixMenu *menu, MatrixNode *node, int dir, BOOL quiet, BOOL keepSteps)
{
    u8 type;
    u8 bit;
    u32 result;
    int columns;
    int i;
    s16 *link;
    MatrixNode *child;
    NeighborIds neighbors;
    u16 k;

    type = node->type;
    switch (type) {
    case 0:
        break;
    case 7:
        bit = 1 << (node->bitIndex + 5);
        if (node->pendingSteps != 0) {
            break;
        }
        if (bit & data_0205fe0c->collectedBits) {
            break;
        }
        data_0205fe0c->collectedBits |= bit;
        data_0205fe0c->crownCount++;
        if (quiet) {
            break;
        }
        menu->eventFlags |= 0x300;
        menu->eventNode = node;
        func_01ffb2f8(menu->effects[1], 2, 0);
        func_01ffb2f8(menu->effects[1], 4, 0);
        func_01ffb2f8(menu->effects[1], 0, 0);
        break;
    case 8:
        bit = 1 << node->bitIndex;
        if (node->pendingSteps != 0) {
            break;
        }
        if (bit & data_0205fe0c->collectedBits) {
            break;
        }
        data_0205fe0c->collectedBits |= bit;
        data_0205fe0c->keyCount++;
        if (quiet) {
            break;
        }
        menu->eventFlags |= 0x400;
        menu->eventNode = node;
        func_01ffb2f8(menu->effects[2], 2, 0);
        func_01ffb2f8(menu->effects[2], 4, 0);
        func_01ffb2f8(menu->effects[2], 0, 0);
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        if (!quiet && type != 9) {
            menu->eventFlags |= 0x600;
            menu->eventParam = node->type - 9;
            menu->eventNode = node;
            func_01ffb2f8(menu->effects[2], 2, 0);
            func_01ffb2f8(menu->effects[2], 4, 0);
            func_01ffb2f8(menu->effects[2], 0, 0);
            PlaySoundEffect(1, 0xb);
        }
        data_0205fe0c->portalBits |= (u8)(1 << (node->type - 9));
        break;
    default:
        if (type >= 14) {
            columns = *menu->map->columns;
            result = 0;
            neighbors = data_ov075_020d14f0;
            node->pendingSteps = 0;
            if (menu->map->levels[node->index] <= data_0205fe0c->currentLevel) {
                func_ov075_020c7fc8(menu->revealState, menu->map, node, node->index);
            }
            if (dir != 0) {
                neighbors.ids[2] = node->index + 1;
            }
            if (dir != 1) {
                neighbors.ids[3] = node->index + columns;
            }
            if (dir != 2) {
                neighbors.ids[0] = node->index - 1;
            }
            if (dir != 3) {
                neighbors.ids[1] = node->index - columns;
            }
            switch (node->type) {
            case 14:
                neighbors.ids[3] = -1;
                neighbors.ids[2] = -1;
                break;
            case 15:
                neighbors.ids[3] = -1;
                neighbors.ids[0] = -1;
                break;
            case 16:
                neighbors.ids[1] = -1;
                neighbors.ids[0] = -1;
                break;
            case 17:
                neighbors.ids[1] = -1;
                neighbors.ids[2] = -1;
                break;
            case 18:
                neighbors.ids[3] = -1;
                neighbors.ids[1] = -1;
                break;
            case 19:
                neighbors.ids[2] = -1;
                neighbors.ids[0] = -1;
                break;
            case 20:
                neighbors.ids[2] = -1;
                break;
            case 21:
                neighbors.ids[3] = -1;
                break;
            case 22:
                neighbors.ids[0] = -1;
                break;
            case 23:
                neighbors.ids[1] = -1;
                break;
            }
            for (k = 0; k < 4; k++) {
                if (neighbors.ids[k] < 0) {
                    continue;
                }
                child = menu->map->nodes[neighbors.ids[k]];
                if (child->type > 2) {
                    if (child->pendingSteps != 0) {
                        child->pendingSteps--;
                    }
                    if (child->type == 0x19) {
                        child = GetNode(menu, node->type == 12 ? child->links[2] : child->links[0]);
                        child->pendingSteps = 0;
                    }
                    result |= PropagateMatrixNodeVisit(menu, child, k, quiet, keepSteps);
                } else {
                    child->visited = 1;
                }
            }
            return result;
        }
        link = node->links;
        result = 0;
        for (i = 0; i < 4; i++, link++) {
            if (*link < 0) {
                continue;
            }
            child = menu->map->nodes[*link];
            if ((child->type > 2 || child->lockValue >= 0)
                && (child->requiredFlag < 0 || IsNodeFlagSet(child))) {
                if (child->pendingSteps != 0) {
                    if (!keepSteps) {
                        child->pendingSteps--;
                    }
                    if (child->pendingSteps == 0 && child->type == 6) {
                        if (!quiet) {
                            menu->eventFlags |= 0x200;
                            menu->eventNode = child;
                            func_01ffb2f8(menu->effects[0], 2, 0);
                            func_01ffb2f8(menu->effects[0], 4, 0);
                            func_01ffb2f8(menu->effects[0], 0, 0);
                        }
                        data_0205fe0c->clearedMask |= 1 << child->bitIndex;
                    }
                }
                if (child->type == 0x19) {
                    child = GetNode(menu, node->type == 12 ? child->links[2] : child->links[0]);
                    child->pendingSteps = 0;
                }
                if (child->type >= 6) {
                    result |= PropagateMatrixNodeVisit(menu, child, i, quiet, keepSteps);
                }
            } else if (child->type <= 2) {
                child->visited = 1;
            }
        }
        return result;
    }
    return 0;
}
