int G3X_GetMtxStackLevelPJ_02006d10(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x2000) >> 13;
    return 0;
}
