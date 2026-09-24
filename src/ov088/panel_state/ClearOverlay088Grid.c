/* Runs both cleanup steps for the shared entry collection.
 * Calls ov027:020b900c and 020b903c with the collection from ov039:020bc1cc; shutdown invokes this after graphics-resource cleanup.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void *func_ov039_020bc1cc(void);
extern void func_ov027_020b900c(void *context);
extern void func_ov027_020b903c(void *context);
void ClearOverlay088Grid(void *unusedContext) {
    func_ov027_020b900c(func_ov039_020bc1cc());
    func_ov027_020b903c(func_ov039_020bc1cc());
}
