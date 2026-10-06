extern void func_ov002_020620fc(int a);
extern int TestContextFlagBit(int slot);
extern int func_ov002_020621c4(int a, int b);
extern void ActivatePanelSlotCD(int mode, int x, int y, int size, int textId);
extern void func_ov002_020627e8(int size[2], int mode, int textId);

void func_ov015_0206eefc(void) {
    int textId;
    int size[2];

    func_ov002_020620fc(0);
    if (TestContextFlagBit(0) != 0 || TestContextFlagBit(1) != 0 || TestContextFlagBit(2) != 0) {
        textId = func_ov002_020621c4(0x26, 0);
        ActivatePanelSlotCD(0, 0x1e, 0x41, 2, textId);
    } else {
        textId = func_ov002_020621c4(0x25, 0);
        ActivatePanelSlotCD(0, 0x1e, 0x46, 2, textId);
    }

    textId = func_ov002_020621c4(0x3c, 0);
    func_ov002_020627e8(size, 0, textId);
    textId = func_ov002_020621c4(0x3c, 0);
    ActivatePanelSlotCD(0, 0x46 - size[0] / 2, 0x62, 2, textId);

    textId = func_ov002_020621c4(0x3d, 0);
    func_ov002_020627e8(size, 0, textId);
    textId = func_ov002_020621c4(0x3d, 0);
    ActivatePanelSlotCD(0, 0xa5 - size[0] / 2, 0x62, 2, textId);
}
