extern void PostPanelEventOff_02066504(int mode, int flags);

void StartPanelFadeIn(int mode)
{
    PostPanelEventOff_02066504(mode, 0x3000);
}
