extern int gResumeModeWorkStorage;

int GetResumeModeResult(void) {
    return *(int *)(*(int *)&gResumeModeWorkStorage + 0x10);
}
