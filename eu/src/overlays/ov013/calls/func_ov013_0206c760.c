extern void ReleaseRecordSlot(int state);
extern void RefreshInactivePanelSlots(void);
extern int DispatchContextCommand(int a, int b, int c, int d);
extern void StopSeqArcOrDefault(int a, int b, int c);
extern void func_ov002_02066a68(void);
extern void func_ov027_020b7e1c(int panel);
extern void DestroyObjectsAndRelease(int panel);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern int data_ov013_02074ce0;

void func_ov013_0206c760(void) {
    ReleaseRecordSlot(9);
    RefreshInactivePanelSlots();
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        StopSeqArcOrDefault(2, 0xd, 4);
    }
    func_ov002_02066a68();
    func_ov027_020b7e1c(data_ov013_02074ce0 + 0x304);
    func_ov027_020b7e1c(data_ov013_02074ce0 + 0x350);
    DestroyObjectsAndRelease(data_ov013_02074ce0 + 0x39c);
    DestroyObjectsAndRelease(data_ov013_02074ce0 + 0x6818);
    NNSi_FndFreeFromDefaultHeap((void *)data_ov013_02074ce0);
}
