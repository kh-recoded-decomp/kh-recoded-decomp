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
