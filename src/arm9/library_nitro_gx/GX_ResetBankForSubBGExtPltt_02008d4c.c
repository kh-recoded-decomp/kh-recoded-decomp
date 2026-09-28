extern void *resetBankForX_();
extern unsigned short data_02056f5e;

void *GX_ResetBankForSubBGExtPltt_02008d4c(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x40000000u;
    return resetBankForX_(&data_02056f5e);
}
