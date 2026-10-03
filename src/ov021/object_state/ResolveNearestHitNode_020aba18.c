#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 data[0x35];
} HitResult;

typedef struct {
    VecFx32 point;
    VecFx32 normal;
} HitContact;

typedef struct HitNode HitNode;

typedef struct {
    u8 pad_00[0x24];
    BOOL (*testHit)(HitNode *node, void *attack, HitContact *contact);
} HitNodeVtbl;

struct HitNode {
    HitNode *next;
    HitNodeVtbl *vtbl;
    u8 pad_08[0x30];
    VecFx32 position;
};

typedef struct {
    HitResult result;
    u32 active;
    HitNode *pending;
} HitScan;

typedef struct {
    u8 pad_00[0x1c];
    s32 kind;
} AttackInfo;

typedef struct {
    u8 pad_00[0x24];
    u16 takeFirst : 1;
    u16 unused1 : 1;
    u16 unused2 : 1;
    u16 applyAll : 1;
} HitOptions;

extern VecFx32 *func_ov001_0206dc4c(void);
extern int Object_GetKindValue_0208744c(HitNode *node);
extern BOOL func_ov021_020ac028(AttackInfo *attack, HitContact *contact, VecFx32 *position);
extern HitResult func_ov021_020abb50(u32 owner, AttackInfo *attack, HitOptions *options, HitContact *contact, HitNode *node);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

BOOL ResolveNearestHitNode_020aba18(u32 owner, AttackInfo *attack, HitOptions *options, HitScan *scan)
{
    VecFx32 *origin = func_ov001_0206dc4c();
    HitNode *found = NULL;
    HitNode *node = scan->pending;
    fx32 bestDistance = 0x7fffffff;
    HitContact contact;
    HitContact best;
    VecFx32 diff;

    scan->pending = NULL;
    for (; node != NULL; node = node->next) {
        BOOL ok;
        if (options != NULL && Object_GetKindValue_0208744c(node) == 2 && (attack->kind == 4 || attack->kind == 3)) {
            continue;
        }
        ok = node->vtbl->testHit(node, attack, &contact);
        if (ok) {
            ok = func_ov021_020ac028(attack, &contact, &node->position);
        }
        if (ok) {
            VecFx32 *position = &node->position;
            if (options != NULL) {
                if (options->applyAll) {
                    scan->result = func_ov021_020abb50(owner, attack, options, &contact, node);
                    found = NULL;
                    continue;
                }
                if (options->takeFirst) {
                    best = contact;
                    found = node;
                    break;
                }
            }
            VEC_Subtract_01ff9e3c(position, origin, &diff);
            if (VEC_Mag_01ff9f28(&diff) < bestDistance) {
                bestDistance = VEC_Mag_01ff9f28(&diff);
                best = contact;
                found = node;
            }
        }
    }
    if (found != NULL) {
        scan->result = func_ov021_020abb50(owner, attack, options, &best, found);
    }
    if (node != NULL) {
        scan->pending = node->next;
    }
    if (scan->pending == NULL) {
        return TRUE;
    }
    return FALSE;
}
