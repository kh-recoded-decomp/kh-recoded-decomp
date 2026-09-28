/* Computes a rounded fixed-point cross product of 3D vectors.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/VEC_CrossProduct.c.
 * Original routine: VEC_CrossProduct. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef int fx32;
typedef long long s64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out)
{
    fx32 x;
    fx32 y;
    fx32 z;

    x = (fx32)(((s64)a->y * b->z - (s64)a->z * b->y + 0x800) >> 12);
    y = (fx32)(((s64)a->z * b->x - (s64)a->x * b->z + 0x800) >> 12);
    z = (fx32)(((s64)a->x * b->y - (s64)a->y * b->x + 0x800) >> 12);
    out->x = x;
    out->y = y;
    out->z = z;
}
