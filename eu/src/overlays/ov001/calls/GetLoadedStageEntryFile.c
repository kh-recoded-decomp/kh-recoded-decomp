extern int *gStageEventContext;

int GetLoadedStageEntryFile(void) {
    return *gStageEventContext;
}
