extern void *OS_WakeupThreadDirect();

void *OSi_SleepAlarmCallback_02002d18(char **slot) {
    char *thread = *slot;
    *slot = 0;
    *(int *)(thread + 0xb0) = 0;
    return OS_WakeupThreadDirect(thread);
}
