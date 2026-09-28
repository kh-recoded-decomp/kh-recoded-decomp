extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int Ov105_IsDeviceReady(void);
extern char *Ov105_GetContext(void);

int SetSessionCallback_0201141c(int callback) {
    int enabled = OS_DisableInterrupts();
    int err = Ov105_IsDeviceReady();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    *(int *)(Ov105_GetContext() + 0xc8) = callback;
    OS_RestoreInterrupts(enabled);
    return 0;
}
