extern void PostPanelEventOn_02066530(int mode, int flags);

void StartPanelFadeOut(int mode)
{
    PostPanelEventOn_02066530(mode, 0x3000);
}
