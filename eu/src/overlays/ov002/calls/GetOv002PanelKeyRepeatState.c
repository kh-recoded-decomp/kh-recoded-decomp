extern int data_ov002_0206c460;

int GetOv002PanelKeyRepeatState(void) {
    return *(int *)&data_ov002_0206c460 + 0x12;
}
