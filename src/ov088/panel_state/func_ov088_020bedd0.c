/* Releases the embedded state at context+0x34 and then performs shared context cleanup.
 * Calls ov027:020ba294 on the embedded state and arm9:020014f0 on its parent context during the shutdown chain.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void func_ov027_020ba294(void *state);
extern void func_020014f0(void *context);
void func_ov088_020bedd0(void *context) {
    func_ov027_020ba294((char *)context + 0x34);
    func_020014f0(context);
}
