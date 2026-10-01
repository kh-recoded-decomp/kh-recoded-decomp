#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Movement {
    fx32 distance;
    VecFx32 direction;
} Movement;

typedef struct KeepFlags {
    BOOL keepFirst;
    BOOL keepSecond;
} KeepFlags;

extern const VecFx32 data_02053438;
extern const KeepFlags data_02055898;

extern void MI_CpuFill8_01ff8830(void *dst, int value, u32 size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern BOOL func_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern fx32 FlipVectorIfDotNegative_0204abd0(VecFx32 *a, const VecFx32 *b);
extern void func_0204af88(VecFx32 *out, const VecFx32 *vec, const VecFx32 *normal, fx32 *dot);
extern BOOL FlagBlockingNormals_0203d994(const VecFx32 *dir, const VecFx32 *motion, const VecFx32 *normals, const u8 *indices,
                                         u8 *hits, int count);
extern BOOL IsAxisInsideVectorCone_0203dd00(const VecFx32 *vecA, const VecFx32 *vecB, const VecFx32 *vecC, const VecFx32 *axis);
extern BOOL func_0203dde0(const VecFx32 *dir, const VecFx32 *a, const VecFx32 *b, const VecFx32 *c);

VecFx32 ResolveSlideMovement_0203deac(const Movement *move, const VecFx32 *normals, int count, u32 *outType, u8 *outPair,
                                      u8 *outList, const VecFx32 *motion)
{
    VecFx32 result;
    u8 finalList[16];
    u8 done[16];
    u8 indices[16];
    u8 hits[16];
    VecFx32 edge;
    VecFx32 saved;
    VecFx32 scaled;
    KeepFlags keep;
    fx32 projection;
    fx32 distance;
    BOOL typeSet;
    u8 idxI;
    u8 idxJ;
    BOOL changed;
    fx32 dotI;
    fx32 dotJ;
    fx32 dot;
    int listCount;
    int n;
    int m;
    u8 doneCount;
    u8 i;
    u8 j;
    u8 k;
    u8 target;

    listCount = 0;
    if (outList != NULL) {
        MI_CpuFill8_01ff8830(outList, 0xff, 16);
    }
    distance = move->distance;
    if (distance == 0) {
        if (outType != NULL) {
            *outType = 0;
        }
        return data_02053438;
    }
    if (count == 0) {
        scaled = move->direction;
        func_0204a5e4(&scaled, distance);
        return scaled;
    }
    result = move->direction;
    typeSet = FALSE;
    if (count == 1) {
        u8 singleHit;

        finalList[0] = 0;
        if (FlagBlockingNormals_0203d994(&move->direction, motion, normals, finalList, &singleHit, count)) {
            count = 0;
            if (outType != NULL) {
                *outType = 3;
                typeSet = TRUE;
            }
            if (outList != NULL) {
                outList[0] = 0;
            }
        }
    } else {
        doneCount = 0;
        for (i = 0; i < count; i++) {
            indices[i] = i;
        }
        for (j = 0; j < count; j++) {
            if (VEC_DotProduct_01ff9e6c(&normals[indices[j]], &move->direction) > 0xff0) {
                count--;
                for (k = j; k < count; k++) {
                    indices[k] = indices[k + 1];
                }
                j--;
            }
        }
        if (FlagBlockingNormals_0203d994(&move->direction, motion, normals, indices, hits, count)) {
            int hitIndex;

            for (hitIndex = 0; hitIndex < count; hitIndex++) {
                if (hits[hitIndex] != 0) {
                    if (outList != NULL) {
                        outList[listCount++] = indices[hitIndex];
                    }
                    count--;
                    for (target = hitIndex; target < count; target++) {
                        indices[target] = indices[target + 1];
                        hits[target] = hits[target + 1];
                    }
                    hitIndex--;
                }
            }
            if (outType != NULL) {
                *outType = 3;
                typeSet = TRUE;
            }
        }
        for (i = 0; i < count - 1; i++) {
            idxI = indices[i];
            for (j = i + 1, target = j; j < count; target = ++j) {
                idxJ = indices[j];
                if (func_0204a9e4(&normals[idxI], &normals[idxJ], &edge)) {
                    if (VEC_DotProduct_01ff9e6c(&normals[idxI], &normals[idxJ]) > 0) {
                        for (k = target + 1; k < count; k++) {
                            indices[k - 1] = indices[k];
                        }
                        count--;
                        j--;
                    }
                    continue;
                }
                dot = VEC_DotProduct_01ff9e6c(&edge, &move->direction);
                VEC_Normalize_01ff9f88(&edge, &edge);
                if (dot < 0) {
                    dot = -dot;
                }
                if (dot < 0x10 && IsAxisInsideVectorCone_0203dd00(&move->direction, &normals[idxI], &normals[idxJ], &edge)) {
                    if (outType != NULL) {
                        *outType = 5;
                    }
                    if (outPair != NULL) {
                        outPair[0] = idxI;
                        outPair[1] = idxJ;
                    }
                    func_0204a5e4(&result, distance);
                    return result;
                }
                dot = FlipVectorIfDotNegative_0204abd0(&edge, &result);
                changed = FALSE;
                if (dot != 0) {
                    for (target = 0; target < count; target++) {
                        if (target != i && target != j
                            && VEC_DotProduct_01ff9e6c(&normals[indices[target]], &edge) > 0) {
                            for (m = 0; m < doneCount; m++) {
                                if (done[m] == target) {
                                    break;
                                }
                            }
                            if (m == doneCount) {
                                for (k = target + 1; k < count; k++) {
                                    indices[k - 1] = indices[k];
                                }
                                count--;
                                if (i >= target) {
                                    j = i;
                                } else if (j >= target) {
                                    j--;
                                }
                                target--;
                                changed = TRUE;
                            }
                        }
                    }
                } else {
                    dotI = VEC_DotProduct_01ff9e6c(&normals[idxI], &move->direction);
                    dotJ = VEC_DotProduct_01ff9e6c(&normals[idxJ], &move->direction);
                    if (dotI < -0xff0 || dotJ < -0xff0) {
                        continue;
                    }
                    if (dotI > dotJ) {
                        target = i;
                    }
                    for (m = 0; m < doneCount; m++) {
                        if (done[m] == target) {
                            break;
                        }
                    }
                    if (m == doneCount) {
                        for (k = target + 1; k < count; k++) {
                            indices[k - 1] = indices[k];
                        }
                        count--;
                        if (dotI > dotJ) {
                            j = i;
                        } else {
                            j--;
                        }
                    }
                    changed = TRUE;
                }
                if (changed) {
                    keep = data_02055898;
                    for (k = 0; k < doneCount; k++) {
                        if (done[k] == i) {
                            keep.keepFirst = FALSE;
                        }
                        if (done[k] == j) {
                            keep.keepSecond = FALSE;
                        }
                    }
                    if (keep.keepFirst) {
                        done[doneCount++] = i;
                    }
                    if (keep.keepSecond) {
                        done[doneCount++] = j;
                    }
                }
            }
        }
        switch (count) {
        case 0:
            break;
        case 2:
            finalList[1] = indices[1];
        case 1:
            finalList[0] = indices[0];
            break;
        default:
            if (func_0203dde0(&move->direction, &normals[indices[0]], &normals[indices[1]], &normals[indices[2]])) {
                if (outType != NULL) {
                    *outType = 6;
                }
                if (outPair != NULL) {
                    for (i = 0; i < count; i++) {
                        outPair[i] = indices[i];
                    }
                }
                return data_02053438;
            }
            MI_CpuCopy8_01ff89a8(indices, finalList, count);
            break;
        }
    }
    if (count != 0) {
        for (i = 0; i < count; i++) {
            dot = VEC_DotProduct_01ff9e6c(&normals[finalList[i]], &move->direction);
            if (dot < 0) {
                dot = -dot;
            }
            if (dot < 0x10) {
                for (k = 0; k < count; k++) {
                    if (k != i) {
                        dot = VEC_DotProduct_01ff9e6c(&normals[finalList[k]], &normals[finalList[i]]);
                        if (dot < 0) {
                            dot = -dot;
                        }
                        if (dot > 0x10 && dot < 0xff0) {
                            break;
                        }
                    }
                }
                if (k == count) {
                    count--;
                    for (j = i; j < count; j++) {
                        finalList[j] = finalList[j + 1];
                    }
                    i--;
                }
            }
        }
    }
    saved = result;
    switch (count) {
    case 0:
        break;
    case 2:
        if (func_0204a9e4(&normals[finalList[0]], &normals[finalList[1]], &result)) {
            count = 1;
        }
        if (count == 2) {
            VEC_Normalize_01ff9f88(&result, &result);
            FlipVectorIfDotNegative_0204abd0(&result, &move->direction);
            dotI = VEC_DotProduct_01ff9e6c(&normals[finalList[0]], &move->direction);
            dotJ = VEC_DotProduct_01ff9e6c(&normals[finalList[1]], &move->direction);
            VEC_Normalize_01ff9f88(&result, &result);
            FlipVectorIfDotNegative_0204abd0(&result, &move->direction);
            break;
        }
        result = saved;
        if (count == 0) {
            break;
        }
    case 1:
        func_0204af88(&result, &result, &normals[finalList[0]], &projection);
        if (projection < -0xff0) {
            if (outType != NULL) {
                *outType = 4;
            }
            count = 0;
            if (outPair != NULL) {
                outPair[0] = finalList[0];
            }
            result = saved;
            typeSet = TRUE;
        } else if (projection > 0xf80) {
            result = saved;
            count = 0;
        }
        break;
    default:
        result = data_02053438;
        break;
    }
    if (count != 0) {
        dot = VEC_DotProduct_01ff9e6c(&move->direction, &result);
        if (dot != 0x1000) {
            if (dot < 0x10) {
                if (outType != NULL && *outType != 3) {
                    *outType = count + 3;
                }
                if (outPair != NULL) {
                    for (n = 0; n < count; n++) {
                        outPair[n] = finalList[n];
                    }
                }
                return data_02053438;
            }
            distance = FX_Div_01ff9c84(distance, dot);
        }
    }
    if (outType != NULL && !typeSet && *outType != 3) {
        *outType = count;
    }
    func_0204a5e4(&result, distance);
    return result;
}
