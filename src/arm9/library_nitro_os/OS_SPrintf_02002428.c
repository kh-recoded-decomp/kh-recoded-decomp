extern void *OS_VSPrintf();

void *OS_SPrintf_02002428(char *dst, const char *fmt, ...) {
    return OS_VSPrintf(dst, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
