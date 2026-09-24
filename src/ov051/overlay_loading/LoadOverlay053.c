/* Loads overlay 53 and runs its initializer. The overlay ID is an absolute
 * linker symbol, not a pointer to memory at that small numeric address.
 * Ghidra caller chain: ov051 selector -> ARM9 overlay loader -> initializer. */
extern char OverlayId053;
extern void LoadOverlay(int processor, int overlayId);
extern void Initialize_ov053_020d21e0(void);
int LoadOverlay053(unsigned int selectionIndex)
{
    int overlayId = (int)&OverlayId053;
    LoadOverlay(0, overlayId);
    Initialize_ov053_020d21e0();
    return overlayId;
}
