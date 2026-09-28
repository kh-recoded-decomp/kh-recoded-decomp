/* Computes fixed-point magnitude of a 3D vector using hardware square root.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/VEC_Mag.c.
 * Original routine: VEC_Mag. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef int fx32;
typedef long long s64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct SqrtRegisters {
    volatile unsigned short control;
    unsigned short padding[3];
    volatile s64 parameter;
} SqrtRegisters;

#define SQRT_REGISTERS ((SqrtRegisters *)0x040002b0)

fx32 VEC_Mag_01ff9f28(const VecFx32 *v)
{
    s64 squared;
    fx32 y = v->y;
    fx32 x = *(volatile const fx32 *)&v->x;

    squared = (s64)x * x;
    squared += (s64)y * y;
    squared += (s64)v->z * v->z;

    SQRT_REGISTERS->control = 1;
    SQRT_REGISTERS->parameter = squared * 4;
    while (SQRT_REGISTERS->control & 0x8000) {
    }
    return (*(volatile fx32 *)0x040002b4 + 1) >> 1;
}
