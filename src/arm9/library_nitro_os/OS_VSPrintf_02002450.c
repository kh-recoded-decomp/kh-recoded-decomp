extern void *Text_VSNPrintf();

void *OS_VSPrintf_02002450(void *dst, const char *fmt, void *ap) {
    return Text_VSNPrintf(dst, 0x7fffffff, fmt, ap);
}
