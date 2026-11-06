extern int gTitleSelectionGlobals;

int GetTitleSessionStatus(void) {
    return *(int *)(*(int *)&gTitleSelectionGlobals + 4);
}
