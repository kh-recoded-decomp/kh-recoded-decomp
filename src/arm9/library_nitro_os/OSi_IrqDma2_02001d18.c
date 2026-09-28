extern void *OSi_IrqCallback();

void *OSi_IrqDma2_02001d18() {
    return OSi_IrqCallback(2);
}
