/* Returns word 0 of the title-session record; its role is separate from status at +4. */

extern int *gTitleSelectionGlobals;

int GetTitleSessionValue(void) {
    return *gTitleSelectionGlobals;
}
