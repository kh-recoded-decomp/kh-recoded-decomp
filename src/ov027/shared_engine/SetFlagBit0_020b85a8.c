void SetFlagBit0_020b85a8(unsigned char *r0, int r1) {
    r0[0x2c] = (r0[0x2c] & ~1) | ((unsigned char)r1 & 1);
}
