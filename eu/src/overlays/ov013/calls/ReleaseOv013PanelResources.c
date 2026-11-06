extern void ReleaseRecordSlot(int state);
extern void RefreshInactivePanelSlots(void);
extern int DispatchContextCommand(int a, int b, int c, int d);
extern void StopSeqArcOrDefault(int a, int b, int c);
extern void ReleaseMenuCursorState(void);
extern void FreeTagTrackerPools(int panel);
extern void DestroyObjectsAndRelease(int panel);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern int gOv013PanelGlobals;

void ReleaseOv013PanelResources(void) {
    ReleaseRecordSlot(9);
    RefreshInactivePanelSlots();
    if (DispatchContextCommand(5, 0, 0, 0) != 0) {
        StopSeqArcOrDefault(2, 0xd, 4);
    }
    ReleaseMenuCursorState();
    FreeTagTrackerPools(gOv013PanelGlobals + 0x304);
    FreeTagTrackerPools(gOv013PanelGlobals + 0x350);
    DestroyObjectsAndRelease(gOv013PanelGlobals + 0x39c);
    DestroyObjectsAndRelease(gOv013PanelGlobals + 0x6818);
    NNSi_FndFreeFromDefaultHeap((void *)gOv013PanelGlobals);
}
