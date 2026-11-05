extern int data_ov001_020a0494;

int GetSessionTimerChannel1Milliseconds(void) {
    return *(int *)(*(int *)&data_ov001_020a0494 + 4);
}
