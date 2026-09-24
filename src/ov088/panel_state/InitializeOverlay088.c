/* Sets up the overlay display, loads its graphics, applies entry states and initializes its handler.
 * The first callback at ov088:020bee60 calls the four setup stages in order and returns1.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
extern void ConfigureOverlay088Display(void);
extern void LoadOverlay088Graphics(void *context);
extern void ApplyOverlay088GridStates(void *context);
extern void func_ov088_020bed0c(void *context);
int InitializeOverlay088(void *context) {
    ConfigureOverlay088Display();
    LoadOverlay088Graphics(context);
    ApplyOverlay088GridStates(context);
    func_ov088_020bed0c(context);
    return 1;
}
