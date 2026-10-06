/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

void func_01ffa624(int *node, const int *source, int unused, int flags) {
    if ((flags & 4) != 0) {
        node[0] |= 1;
    } else {
        node[1] = source[0];
        node[2] = source[1];
        node[3] = source[2];
    }

    node[0] |= 0x18;
}
