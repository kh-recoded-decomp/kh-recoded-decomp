extern int LoadOverlay053(unsigned int selectionIndex);
extern int LoadOverlay059(unsigned int selectionIndex);
extern int LoadOverlay060(unsigned int selectionIndex);
extern int LoadNextOverlayForSelection(unsigned int selectionIndex);
int LoadOverlayForMode(unsigned int selectionIndex, int mode)
{
    switch ((unsigned int)mode + 1U) {
    case 0: return LoadOverlay060(selectionIndex);
    case 2: return LoadOverlay059(selectionIndex);
    case 3: return LoadNextOverlayForSelection(selectionIndex);
    case 1:
    default: return LoadOverlay053(selectionIndex);
    }
}
