/* Restores geometry FIFO interrupt state after DMA completion, clears busy state, and dispatches the saved completion callback.
 * Evidence: Saved callback fields, IRQ restoration, GXSTAT bits, and callback dispatch in source.
 * Uncertainty: SDK callback association is established by the source comment; opaque shared-work layout remains partly offset-based.
 * Source: src/calls/MIi_DMACallback.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef void (*OSIrqFunction)(void *arg);

extern unsigned int OS_DisableIrqMask(unsigned int mask);
extern void OS_SetIrqFunction(unsigned int intrBits, OSIrqFunction function);
extern int data_02056ee8;


void geometry_fifo_dma_complete_02005584(void) {
    void (*completionCallback)(void *);
    void *completionArgument;

    OS_DisableIrqMask(0x200000);

    *(volatile unsigned int *)0x04000600 =
        (*(unsigned int *)((char *)&data_02056ee8 + 0x18) << 30) |
        (*(volatile unsigned int *)0x04000600 & ~0xc0000000);

    OS_SetIrqFunction(0x200000, *(OSIrqFunction *)((char *)&data_02056ee8 + 0x1c));

    data_02056ee8 = 0;
    completionCallback = *(void (**)(void *))((int)&data_02056ee8 + 0x10);
    completionArgument = *(void **)((int)&data_02056ee8 + 0x14);
    if (completionCallback != 0) {
        completionCallback(completionArgument);
    }
}
