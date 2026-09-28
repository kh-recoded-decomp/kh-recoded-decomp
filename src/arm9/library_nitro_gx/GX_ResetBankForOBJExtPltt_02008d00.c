extern void *resetBankForX_();
extern unsigned short data_02056f58;

void *GX_ResetBankForOBJExtPltt_02008d00(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4000000;
    *dispcnt = *dispcnt & ~0x80000000;
    return resetBankForX_(&data_02056f58);
}
