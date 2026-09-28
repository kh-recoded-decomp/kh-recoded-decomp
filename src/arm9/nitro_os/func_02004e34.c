void MI_SetWramBank(unsigned char bank) {
    *(volatile unsigned char *)0x04000247 = bank;
}
