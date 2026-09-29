#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Bounds {
    VecFx32 max;
    VecFx32 min;
} Bounds;

typedef struct QuadItem {
    struct QuadNode *owner;
    struct QuadItem *next;
    struct QuadItem *prev;
    u8 flags;
    u8 hasSweep;
    u8 pad_0e[0x1a];
    Bounds bounds;
    u8 pad_40[0x10];
    Bounds sweptBounds;
} QuadItem;

typedef struct QuadNode {
    u16 flags;
    u8 pad_02[6];
    QuadItem *head;
    u8 pad_0c[4];
    struct QuadNode *child[4];
} QuadNode;

typedef struct QuadRect {
    fx32 x;
    fx32 z;
    fx32 size;
} QuadRect;

void QuadTree_Insert_02033a90(QuadNode *node, const QuadRect *rect, QuadItem *item) {
    int quarter = rect->size / 4;
    int q = -1;
    Bounds *bounds;
    QuadRect sub;

    bounds = item->hasSweep ? &item->sweptBounds : &item->bounds;
    if (bounds->max.x < rect->x) {
        if (bounds->max.z < rect->z) {
            q = 0;
        } else if (bounds->min.z >= rect->z) {
            q = 2;
        }
    } else if (bounds->min.x >= rect->x) {
        if (bounds->max.z < rect->z) {
            q = 1;
        } else if (bounds->min.z >= rect->z) {
            q = 3;
        }
    }
    if (q < 0 || node->child[q] == NULL) {
        item->next = node->head;
        if (item->next != NULL) {
            node->head->prev = item;
        }
        node->head = item;
        item->owner = node;
        return;
    }
    switch (q) {
    case 0:
        sub.x = rect->x - quarter;
        sub.z = rect->z - quarter;
        break;
    case 1:
        sub.x = rect->x + quarter;
        sub.z = rect->z - quarter;
        break;
    case 2:
        sub.x = rect->x - quarter;
        sub.z = rect->z + quarter;
        break;
    default:
        sub.x = rect->x + quarter;
        sub.z = rect->z + quarter;
        break;
    }
    sub.size = rect->size / 2;
    node->flags |= 0x1000 << q;
    QuadTree_Insert_02033a90(node->child[q], &sub, item);
}
