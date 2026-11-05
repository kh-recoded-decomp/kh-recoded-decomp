extern int *data_ov001_020a04e8;

int GetPanelSelectedRecordName(void) {
    return *(int *)((char *)data_ov001_020a04e8 + 0x1c);
}
