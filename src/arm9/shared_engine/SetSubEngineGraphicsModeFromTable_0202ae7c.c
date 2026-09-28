extern void GXS_SetGraphicsMode(int mode);

void SetSubEngineGraphicsModeFromTable_0202ae7c(int *table) {
    int mode = table[*(volatile unsigned int *)0x4001000 & 7];
    if (mode >= 8) {
        mode -= 8;
    }
    GXS_SetGraphicsMode(mode);
}
