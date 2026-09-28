extern int Ov105_IsDeviceReady(void);
extern void DC_InvalidateRange(void *addr, unsigned int size);
extern char data_020597fc[];

int PollDeviceStatus_0201105c(void) {
    int r = Ov105_IsDeviceReady();
    if (r == 0) {
        DC_InvalidateRange(*(void **)(*(int *)(data_020597fc + 4) + 4), 2);
        if (**(unsigned short **)(*(int *)(data_020597fc + 4) + 4) <= 1) {
            r = 3;
        } else {
            r = 0;
        }
        return r;
    }
    return r;
}
