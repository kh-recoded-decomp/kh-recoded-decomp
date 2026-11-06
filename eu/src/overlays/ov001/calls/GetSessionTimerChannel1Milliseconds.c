extern int gSessionTimerWork;

int GetSessionTimerChannel1Milliseconds(void) {
    return *(int *)(*(int *)&gSessionTimerWork + 4);
}
