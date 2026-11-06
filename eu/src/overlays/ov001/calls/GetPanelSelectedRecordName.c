extern int *gSubscenePanelWork;

int GetPanelSelectedRecordName(void) {
    return *(int *)((char *)gSubscenePanelWork + 0x1c);
}
