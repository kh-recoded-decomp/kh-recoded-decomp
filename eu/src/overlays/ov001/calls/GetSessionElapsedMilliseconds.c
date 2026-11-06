extern int *gSessionTimerWork;

int GetSessionElapsedMilliseconds(void) {
    return *gSessionTimerWork;
}
