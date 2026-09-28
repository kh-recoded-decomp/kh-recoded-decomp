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
