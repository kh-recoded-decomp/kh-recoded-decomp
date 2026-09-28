/* Computes rounded fixed-point dot product of two 3D vectors.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/VEC_DotProduct.c.
 * Original routine: VEC_DotProduct. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b)
{
    long long sum = (long long)a->x * b->x
                  + (long long)a->y * b->y
                  + (long long)a->z * b->z;

    return (fx32)((sum + 0x800) >> 12);
}
