extern void *OSi_IrqCallback();

void *OSi_IrqDma0_02001cf8() {
    return OSi_IrqCallback(0);
}
