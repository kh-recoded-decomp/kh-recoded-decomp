extern int Slot_SetVisible();

void SetEntrySlotsVisible_020b9580(int a, int *b, int c) {
    unsigned int x;
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            Slot_SetVisible(a, v, c);
        }
    }
    x = ((c != 0) ? 1u : 0u) << 31;
    b[37] = (((unsigned int)b[37]) & ~2u) | (x >> 30);
}
