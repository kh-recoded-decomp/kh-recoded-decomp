/* Based on src/auto/func_020200c8.character from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int LengthTerminatedHalfwords(unsigned short *text) {
    int length = -1;
    unsigned short character;
    do {
        character = *text++;
        length++;
    } while (character != 0);
    return length;
}
