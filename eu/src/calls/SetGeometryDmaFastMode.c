/* First word only of the existing eight-word BSS allocation; not an RNG seed. */
extern int data_01fffea0;

void SetGeometryDmaFastMode(int mode) {
    data_01fffea0 = mode;
}
