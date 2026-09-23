/* Behavior: Adds a scaled fixed point vector to a base vector.
 * Inputs/outputs and evidence: For each axis computes base + (scale times vector shifted by 27).
 * Uncertainty: The unusual shift is preserved exactly; interpretation as a normalized scale depends on caller units.
 * Source: khdays-decomp/src/calls/func_01ffd0e8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector)
{
    resultVector->x = baseVector->x + (fx32)(((fx64)scale * scaledVector->x) >> 27);
    resultVector->y = baseVector->y + (fx32)(((fx64)scale * scaledVector->y) >> 27);
    resultVector->z = baseVector->z + (fx32)(((fx64)scale * scaledVector->z) >> 27);
}
