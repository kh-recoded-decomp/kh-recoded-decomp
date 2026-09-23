/* Resets the geometry engine matrix stack and restores its matrix mode/state.
 * Evidence: GXSTAT and geometry matrix register writes in source.
 * Uncertainty: SDK alias suffix is link-level only.
 * Source: src/calls/G3X_ResetMtxStack_2.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef unsigned int u32;
typedef volatile u32 REGType32v;

#define reg_G3_GXSTAT        (*(REGType32v *)0x4000600)
#define reg_G3_MTX_MODE      (*(REGType32v *)0x4000440)
#define reg_G3_MTX_POP       (*(REGType32v *)0x4000448)
#define reg_G3_MTX_IDENTITY  (*(REGType32v *)0x4000454)

extern int G3X_GetMtxStackLevelPV(int *level);
extern int G3X_GetMtxStackLevelPJ(int *level);

void reset_geometry_matrix_stack_02006b00(void) {
    int pvLevel;
    int pjLevel;

    reg_G3_GXSTAT |= 0x8000;

    while (G3X_GetMtxStackLevelPV(&pvLevel) != 0) {}
    while (G3X_GetMtxStackLevelPJ(&pjLevel) != 0) {}

    reg_G3_MTX_MODE = 3;
    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 0;

    if (pjLevel != 0) {
        reg_G3_MTX_POP = pjLevel;
    }

    reg_G3_MTX_MODE = 2;
    reg_G3_MTX_POP = pvLevel;
    reg_G3_MTX_IDENTITY = 0;
}
