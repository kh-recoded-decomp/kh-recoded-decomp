extern int gFieldEntryPoolManager;

unsigned short GetActiveFieldEntryListCount(void) {
    return *(unsigned short *)(*(int *)&gFieldEntryPoolManager + 6);
}
