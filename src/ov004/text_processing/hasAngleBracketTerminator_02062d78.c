int hasAngleBracketTerminator_02062d78(unsigned short *text, int mode) {
    unsigned short firstCodeUnit;
    if (text == 0) {
        return 0;
    }
    firstCodeUnit = *text;
    if (firstCodeUnit == 0x3c) {
        return 1;
    }
    if (firstCodeUnit != 0) {
        do {
            text++;
        } while (*text != 0);
    }
    return text[-1] == 0x3e || mode == 2;
}
