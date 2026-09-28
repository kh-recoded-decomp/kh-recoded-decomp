int G3X_GetMtxStackLevelPV_02006ce4(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x1f00) >> 8;
    return 0;
}
