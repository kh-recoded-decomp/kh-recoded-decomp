/* Loads overlay 59 and runs its initializer. The overlay ID is an absolute
 * linker symbol, not a pointer to memory at that small numeric address.
 * Ghidra caller chain: ov051 selector -> ARM9 overlay loader -> initializer. */
extern char OverlayId059;
extern void LoadOverlay(int processor, int overlayId);
extern void Initialize_ov059_020c7460(void);
int LoadOverlay059(unsigned int selectionIndex)
{
    int overlayId = (int)&OverlayId059;
    LoadOverlay(0, overlayId);
    Initialize_ov059_020c7460();
    return overlayId;
}
