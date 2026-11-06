extern int gOv002ProfilePanelWork;

int GetOv002PanelKeyRepeatState(void) {
    return *(int *)&gOv002ProfilePanelWork + 0x12;
}
