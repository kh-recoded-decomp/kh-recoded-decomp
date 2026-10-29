extern void PopPanelState_020c6218(int state, int parameter);

void PanelScene_HandleCancel(int state)
{
    PopPanelState_020c6218(state, -1);
}
