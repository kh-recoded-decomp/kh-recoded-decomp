/* Tests whether a point lies inside inclusive bounds stored as four bytes at offsets 0x1c through 0x1f.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/auto/func_ov026_02082c9c.c. */
struct Box {
    unsigned char pad[0x1c];
    unsigned char x;
    unsigned char y;
    unsigned char w;
    unsigned char h;
};

int func_ov027_020b7860(int px, int py, struct Box *b) {
    int r = 0;
    if (b->x <= px && px <= b->x + b->w && b->y <= py && py <= b->y + b->h) {
        r = 1;
    }
    return r;
}
