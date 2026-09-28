/* Runs the graphics-resource cleanup operation for the shared state used by overlay 88.
 * Gets the same ov039:020bc1a4 state used by resource loading, then invokes ov027:020b7f8c with argument0 during the shutdown chain.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void *func_ov039_020bc18c(void);
extern void func_ov027_020b7f8c(void *context, int flags);
void func_ov089_020bf488(void) { func_ov027_020b7f8c(func_ov039_020bc18c(), 0); }
