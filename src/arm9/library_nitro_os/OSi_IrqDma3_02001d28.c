extern void *OSi_IrqCallback();

void *OSi_IrqDma3_02001d28() {
    return OSi_IrqCallback(3);
}
