extern char data_0205a8d0;
extern char data_02047370_budget;
extern void *ResetTaskQueue_();

void *GfxQueue_Configure_02013fd0(int a, int b) {
    int *ctx = (int *)&data_0205a8d0;
    ctx[0] = a;
    ctx[1] = b;
    return ResetTaskQueue_(&data_02047370_budget);
}
