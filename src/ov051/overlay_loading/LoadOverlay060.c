/* Loads overlay 60 and runs its initializer. The overlay ID is an absolute
 * linker symbol, not a pointer to memory at that small numeric address.
 * Ghidra caller chain: ov051 selector -> ARM9 overlay loader -> initializer. */
extern char OverlayId060;
extern void LoadOverlay(int processor, int overlayId);
extern void Initialize_ov060_020c7460(void);
int LoadOverlay060(unsigned int selectionIndex)
{
    int overlayId = (int)&OverlayId060;
    LoadOverlay(0, overlayId);
    Initialize_ov060_020c7460();
    return overlayId;
}
