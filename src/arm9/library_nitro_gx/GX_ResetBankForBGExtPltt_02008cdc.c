extern void *resetBankForX_();
extern unsigned short data_02056f56;

void *GX_ResetBankForBGExtPltt_02008cdc(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4000000;
    *dispcnt = *dispcnt & ~0x40000000;
    return resetBankForX_(&data_02056f56);
}
