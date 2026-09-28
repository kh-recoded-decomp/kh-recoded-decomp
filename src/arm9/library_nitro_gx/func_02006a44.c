extern void GXi_NopClearFifo128_(volatile unsigned int *fifo);

void G3X_ClearFifo_02006a44(void) {
    GXi_NopClearFifo128_((volatile unsigned int *)0x4000400);
    while (*(volatile unsigned int *)0x4000600 & 0x8000000) {
        ;
    }
}
