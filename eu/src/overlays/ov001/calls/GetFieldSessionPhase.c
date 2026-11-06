extern int *gFieldSessionWork;

int GetFieldSessionPhase(void) {
    return *(int *)((char *)gFieldSessionWork + 0x1c);
}
