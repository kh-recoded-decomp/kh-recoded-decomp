/* A free eligible slot must exist. The original code does not supply a valid
 * overlay ID or slot on the no-slot path; callers must uphold this contract. */
extern const unsigned char *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void LoadOverlay(int processor, int overlayId);
extern int availableOverlayIds[][3];
extern void (*overlayInitializers[][3])(void);
extern int loadedOverlayIds[3];
int LoadNextOverlayForSelection(unsigned int selectionIndex)
{
    int selection = *GetOverlaySelectionRecord(selectionIndex);
    int overlayId;
    int slot;
    for (slot = 2; slot >= 0; --slot) {
        if (loadedOverlayIds[slot] == -1 && availableOverlayIds[selection][slot] != -1 && overlayInitializers[selection][slot]) {
            overlayId = availableOverlayIds[selection][slot];
            loadedOverlayIds[slot] = overlayId;
            break;
        }
    }
    LoadOverlay(0, overlayId);
    if (overlayInitializers[selection][slot]) {
        overlayInitializers[selection][slot]();
    }
    return overlayId;
}
