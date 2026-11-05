extern void ResetOv002SubPanelText(int a);
extern int TestContextFlagBit(int slot);
extern int GetOv002PanelMessage(int a, int b);
extern void ActivatePanelSlotCD(int mode, int x, int y, int size, int textId);
extern void MeasurePanelTextPrimary(int size[2], int mode, int textId);

void func_ov015_0206eefc(void) {
    int textId;
    int size[2];

    ResetOv002SubPanelText(0);
    if (TestContextFlagBit(0) != 0 || TestContextFlagBit(1) != 0 || TestContextFlagBit(2) != 0) {
        textId = GetOv002PanelMessage(0x26, 0);
        ActivatePanelSlotCD(0, 0x1e, 0x41, 2, textId);
    } else {
        textId = GetOv002PanelMessage(0x25, 0);
        ActivatePanelSlotCD(0, 0x1e, 0x46, 2, textId);
    }

    textId = GetOv002PanelMessage(0x3c, 0);
    MeasurePanelTextPrimary(size, 0, textId);
    textId = GetOv002PanelMessage(0x3c, 0);
    ActivatePanelSlotCD(0, 0x46 - size[0] / 2, 0x62, 2, textId);

    textId = GetOv002PanelMessage(0x3d, 0);
    MeasurePanelTextPrimary(size, 0, textId);
    textId = GetOv002PanelMessage(0x3d, 0);
    ActivatePanelSlotCD(0, 0xa5 - size[0] / 2, 0x62, 2, textId);
}
