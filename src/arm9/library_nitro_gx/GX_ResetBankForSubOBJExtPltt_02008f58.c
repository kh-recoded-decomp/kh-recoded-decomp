extern void *resetBankForX_();
extern unsigned short data_02056f60;

void *GX_ResetBankForSubOBJExtPltt_02008f58(void) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = *dispcnt & ~0x80000000u;
    return resetBankForX_(&data_02056f60);
}
