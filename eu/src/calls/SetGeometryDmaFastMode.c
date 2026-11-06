/* First word only of the existing eight-word BSS allocation; not an RNG seed. */
extern int gGeometryDmaFastModeStorage;

void SetGeometryDmaFastMode(int mode) {
    gGeometryDmaFastModeStorage = mode;
}
