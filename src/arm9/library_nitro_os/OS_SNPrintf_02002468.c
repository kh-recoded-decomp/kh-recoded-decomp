extern void *Text_VSNPrintf();

void *OS_SNPrintf_02002468(char *dst, unsigned int len, const char *fmt, ...) {
    return Text_VSNPrintf(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
