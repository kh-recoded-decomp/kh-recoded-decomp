extern void *OSi_IrqCallback();

void *OSi_IrqDma1_02001d08() {
    return OSi_IrqCallback(1);
}
