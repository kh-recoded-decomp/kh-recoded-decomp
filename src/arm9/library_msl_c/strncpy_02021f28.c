char *strncpy_02021f28(char *dst, const char *src, unsigned n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    unsigned char *p;
    if (n == 0) {
        return dst;
    }
    do {
        p = d;
        *d++ = *s++;
        if (*p == 0) {
            while (--n != 0) {
                *d++ = 0;
            }
            return dst;
        }
    } while (--n != 0);
    return dst;
}
