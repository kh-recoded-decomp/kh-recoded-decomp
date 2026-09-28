/* Adds a scaled fixed-point vector to another vector.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/VEC_MultAdd.c.
 * Original routine: VEC_MultAdd. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct { int x, y, z; } VecFx32;

void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst) {
    dst->x = add->x + (int)(((long long)scale * v->x) >> 12);
    dst->y = add->y + (int)(((long long)scale * v->y) >> 12);
    dst->z = add->z + (int)(((long long)scale * v->z) >> 12);
}
