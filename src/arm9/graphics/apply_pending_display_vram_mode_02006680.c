extern unsigned short data_02056f08;
extern short data_02055c18;
void apply_pending_display_vram_mode_02006680(void) {
    volatile unsigned int *displayControl = (volatile unsigned int *)0x04000000;
    unsigned short pendingMode;
    data_02055c18 = 1;
    pendingMode = data_02056f08;
    if (pendingMode != 0) {
        *displayControl = *displayControl & 0xfffcffff | (unsigned int)pendingMode << 0x10;
        return;
    }
    *displayControl = *displayControl | 0x10000;
}
