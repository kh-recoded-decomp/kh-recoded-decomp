extern int data_ov001_020a04fc;

unsigned short GetActiveFieldEntryListCount(void) {
    return *(unsigned short *)(*(int *)&data_ov001_020a04fc + 6);
}
