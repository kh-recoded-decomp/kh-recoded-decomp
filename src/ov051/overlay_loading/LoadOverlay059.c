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
