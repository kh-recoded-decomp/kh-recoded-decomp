/* Configures background layers and enables the display layers used by overlay 88.
 * Writes the secondary-engine BG2/BG3 control fields while preserving bits0x43, then selects display layers0x1c00.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void func_0200672c(int enabled);
void ConfigureOverlay088Display(void) {
    func_0200672c(0);
    *(volatile unsigned short *)0x0400100c = (*(volatile unsigned short *)0x0400100c & 0x43) | 0xe00;
    *(volatile unsigned short *)0x0400100e = (*(volatile unsigned short *)0x0400100e & 0x43) | 0xf80;
    *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00U) | 0x1c00;
}
