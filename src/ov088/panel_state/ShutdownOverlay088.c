/* Releases the overlay graphics, entry collection and embedded handler state.
 * The second callback at ov088:020bee64 calls the three cleanup stages in order.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void ReleaseOverlay088Graphics(void);
extern void ClearOverlay088Grid(void *context);
extern void func_ov088_020bedd0(void *context);
void ShutdownOverlay088(void *context) {
    ReleaseOverlay088Graphics();
    ClearOverlay088Grid(context);
    func_ov088_020bedd0(context);
}
