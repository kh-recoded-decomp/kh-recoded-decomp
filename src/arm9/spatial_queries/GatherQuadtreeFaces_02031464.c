#include "nitro/types.h"

typedef struct CollBox {
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
} CollBox;

typedef struct CollFace {
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    u16 flags;
} CollFace;

typedef struct CollFace88 {
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    u16 flags;
    u8 pad_12[0x88 - 0x12];
} CollFace88;

typedef struct CollFace84 {
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    u16 flags;
    u8 pad_12[0x84 - 0x12];
} CollFace84;

typedef struct CollFaceFlagBits {
    u16 low : 15;
    u16 last : 1;
} CollFaceFlagBits;

typedef struct CollFaceRef {
    CollFace *face;
    s32 kind;
} CollFaceRef;

typedef struct CollFilterArgs {
    CollFaceRef ref;
    CollFaceRef hit;
} CollFilterArgs;

typedef struct CollFaceCursor {
    CollFace *face;
    s32 kind;
    u32 reserved;
} CollFaceCursor;

typedef BOOL (*CollFilterFn)(CollFilterArgs *args, void *user, s32 limit, s32 zero);

typedef struct CollGatherQuery {
    u8 pad_00[4];
    CollFace88 *floorFaces;
    CollFace84 *wallFaces;
    CollFace84 *ceilFaces;
    u8 pad_10[0x93 - 0x10];
    u8 kindMask;
    u8 pad_94[4];
    CollFilterFn filter;
    void *filterUser;
    CollBox *box;
    CollFace **floorList;
    CollFace **wallList;
    CollFace **ceilList;
    s32 limit;
    s16 *floorCount;
    s16 *wallCount;
    s16 *ceilCount;
} CollGatherQuery;

typedef struct CollNode {
    u16 flags;
    s16 floorIndex;
    s16 wallIndex;
    s16 ceilIndex;
    u8 pad_08[4];
    struct CollNode *parent;
    struct CollNode *children[4];
} CollNode;

typedef struct CollTraversalFrame {
    s16 childIndex;
    u16 nodeFlags;
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollTraversalFrame;

extern BOOL func_01ffb328(CollFace *face, CollBox *box);
extern CollTraversalFrame *data_027e00b0;
extern CollTraversalFrame data_027e00b4;

static inline BOOL CollGather_RunFilter(CollFilterFn filter, CollFilterArgs *args, s32 limit, void *user, CollFace *face, s32 kind) {
    args->hit.face = face;
    args->hit.kind = kind;
    return filter(args, user, limit, 0);
}

/* Cursor face is reread after every store. */
static inline BOOL CollGather_AcceptFace(CollGatherQuery *query, volatile CollFaceCursor *cursor, s32 kind) {
    CollFilterArgs args;
    CollBox *box = query->box;
    CollFace *face = cursor->face;

    if (box->maxX < face->minX || box->minX > face->maxX || box->maxZ < face->minZ || box->minZ > face->maxZ) {
        return FALSE;
    }
    if (!func_01ffb328(face, box)) {
        return FALSE;
    }
    if (face->flags & 0x4000) {
        return FALSE;
    }
    if (query->filter != NULL) {
        args.ref.face = face;
        args.ref.kind = kind;
        if (!CollGather_RunFilter(query->filter, &args, query->limit, query->filterUser, face, kind)) {
            return FALSE;
        }
    }
    return TRUE;
}

void GatherQuadtreeFaces_02031464(CollNode *node, CollGatherQuery *query) {
    CollFaceCursor ref;
    u32 useFloor;
    u32 useWall;
    u32 useCeil;
    u32 mask0;
    u32 mask1;
    u32 mask2;
    u32 mask3;
    CollFace *face;
    s32 quarter;
    u16 nodeFlags;
    CollBox *box;
    CollTraversalFrame *nextFrame;
    s32 centerX;
    CollTraversalFrame *frame;
    CollTraversalFrame *parentFrame;
    u16 siblingFlags;
    s32 descentChild;
    s32 siblingChild;
    s16 previousChild;
    s16 count;
    s16 *countPtr;

    useFloor = query->kindMask & 1;
    useWall = query->kindMask & 2;
    useCeil = query->kindMask & 4;
    if (useFloor != 0) {
        mask0 = 1;
        mask1 = 2;
        mask2 = 4;
        mask3 = 8;
    } else {
        mask0 = 0;
        mask1 = 0;
        mask2 = 0;
        mask3 = 0;
    }
    if (useWall != 0) {
        mask0 |= 0x10;
        mask1 |= 0x20;
        mask2 |= 0x40;
        mask3 |= 0x80;
    }
    if (useCeil != 0) {
        mask0 |= 0x100;
        mask1 |= 0x200;
        mask2 |= 0x400;
        mask3 |= 0x800;
    }

restart:
    if (useFloor != 0 && node->floorIndex >= 0) {
        ref.kind = 1;
        ref.face = (CollFace *)&query->floorFaces[node->floorIndex];
        for (;;) {
            if (CollGather_AcceptFace(query, &ref, 1)) {
                countPtr = query->floorCount;
                count = *countPtr;
                if (count >= *(s16 *)&query->limit) {
                    useFloor = 0;
                    *countPtr = -1;
                    break;
                }
                *countPtr = count + 1;
                query->floorList[count] = ((volatile CollFaceCursor *)&ref)->face;
            }
            face = ((volatile CollFaceCursor *)&ref)->face;
            if (((CollFaceFlagBits *)&face->flags)->last) {
                break;
            }
            ref.face = (CollFace *)((CollFace88 *)face + 1);
        }
    }
    if (useWall != 0 && node->wallIndex >= 0) {
        ref.kind = 2;
        ref.face = (CollFace *)&query->wallFaces[node->wallIndex];
        for (;;) {
            if (CollGather_AcceptFace(query, &ref, 2)) {
                countPtr = query->wallCount;
                count = *countPtr;
                if (count >= *(s16 *)&query->limit) {
                    useWall = 0;
                    *countPtr = -1;
                    break;
                }
                *countPtr = count + 1;
                query->wallList[count] = ((volatile CollFaceCursor *)&ref)->face;
            }
            face = ((volatile CollFaceCursor *)&ref)->face;
            if (((CollFaceFlagBits *)&face->flags)->last) {
                break;
            }
            ref.face = (CollFace *)((CollFace84 *)face + 1);
        }
    }
    if (useCeil != 0 && node->ceilIndex >= 0) {
        ref.kind = 3;
        ref.face = (CollFace *)&query->ceilFaces[node->ceilIndex];
        for (;;) {
            if (CollGather_AcceptFace(query, &ref, 3)) {
                countPtr = query->ceilCount;
                count = *countPtr;
                if (count >= *(s16 *)&query->limit) {
                    useCeil = 0;
                    *countPtr = -1;
                    break;
                }
                *countPtr = count + 1;
                query->ceilList[count] = ((volatile CollFaceCursor *)&ref)->face;
            }
            face = ((volatile CollFaceCursor *)&ref)->face;
            if (((CollFaceFlagBits *)&face->flags)->last) {
                break;
            }
            ref.face = (CollFace *)((CollFace84 *)face + 1);
        }
    }

    nodeFlags = node->flags;
    frame = data_027e00b0;
    if (nodeFlags != 0) {
        nextFrame = frame + 1;
        box = query->box;
        quarter = frame->size / 4;
        centerX = frame->centerX;
        if (box->maxX < centerX) {
            nodeFlags &= 0x5555;
        } else if (box->minX > centerX) {
            nodeFlags &= 0xaaaa;
        }
        if (box->maxZ < frame->centerZ) {
            nodeFlags &= 0x3333;
        } else if (box->minZ > frame->centerZ) {
            nodeFlags &= 0xcccc;
        }

        descentChild = 0xf;
        if (nodeFlags & mask0) {
            nextFrame->centerX = centerX - quarter;
            descentChild = 0;
            nextFrame->centerZ = frame->centerZ - quarter;
        } else if (nodeFlags & mask1) {
            nextFrame->centerX = centerX + quarter;
            descentChild = 1;
            nextFrame->centerZ = frame->centerZ - quarter;
        } else if (nodeFlags & mask2) {
            nextFrame->centerX = centerX - quarter;
            descentChild = 2;
            nextFrame->centerZ = frame->centerZ + quarter;
        } else if (nodeFlags & mask3) {
            nextFrame->centerX = centerX + quarter;
            descentChild = 3;
            nextFrame->centerZ = frame->centerZ + quarter;
        }

        if (descentChild != 0xf) {
            node = node->children[descentChild];
            nextFrame->childIndex = descentChild;
            frame->nodeFlags = nodeFlags;
            data_027e00b0 = nextFrame;
            goto restart;
        }
    }

    while (frame != &data_027e00b4) {
        previousChild = frame->childIndex;
        if (previousChild == 3) {
            frame--;
            node = node->parent;
            continue;
        }

        parentFrame = frame - 1;
        node = node->parent;
        siblingFlags = parentFrame->nodeFlags;
        quarter = parentFrame->size / 4;
        siblingChild = 0;

        switch (previousChild) {
        case 0:
            if (siblingFlags & mask1) {
                frame->centerX = parentFrame->centerX + quarter;
                siblingChild = 1;
                frame->centerZ = parentFrame->centerZ - quarter;
                break;
            }
        case 1:
            if (siblingFlags & mask2) {
                frame->centerX = parentFrame->centerX - quarter;
                siblingChild = 2;
                frame->centerZ = parentFrame->centerZ + quarter;
                break;
            }
        case 2:
            if (siblingFlags & mask3) {
                frame->centerX = parentFrame->centerX + quarter;
                siblingChild = 3;
                frame->centerZ = parentFrame->centerZ + quarter;
            }
            break;
        }

        if (siblingChild != 0) {
            node = node->children[siblingChild];
            frame->childIndex = siblingChild;
            data_027e00b0 = frame;
            goto restart;
        }
        frame--;
    }
}
