extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int Ov105_IsDeviceReady(void);
extern int Ov105_WMi_CheckStateEx(int a, int b);
extern void Ov105_ClearSharedRequestBit(void);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern char data_020597fc;

int ShutdownWireless_02010ee0(void) {
    int enabled = OS_DisableInterrupts();
    int err;
    if (Ov105_IsDeviceReady() != 0) {
        OS_RestoreInterrupts(enabled);
        return 3;
    }
    err = Ov105_WMi_CheckStateEx(1, 0);
    if (err != 0) {
        return err;
    }
    Ov105_ClearSharedRequestBit();
    PXI_SetFifoRecvCallback(0xa, 0);
    *(int *)((char *)&data_020597fc + 4) = 0;
    *(short *)&data_020597fc = 0;
    OS_RestoreInterrupts(enabled);
    return 0;
}
