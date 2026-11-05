extern int data_ov033_020baae0;

int GetResumeModeResult(void) {
    return *(int *)(*(int *)&data_ov033_020baae0 + 0x10);
}
