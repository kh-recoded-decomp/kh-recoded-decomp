/* Computes rounded fixed-point dot product of 32-bit and 16-bit vectors.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/calls/VEC_DotProductFx16.c.
 * Original routine: VEC_DotProductFx16. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef int fx32;
typedef short fx16;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx16 x, y, z; } VecFx16;

fx32 VEC_DotProductFx16_0202ffb8(const VecFx32 *v, const VecFx16 *m)
{
    long long s = (long long)v->x * m->x
                + (long long)v->y * m->y
                + (long long)v->z * m->z;
    return (fx32)((s + 0x800) >> 12);
}
