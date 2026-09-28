extern char data_020597fc[];

void SetCommandArg_02010f28(int idx, int value) {
    *(int *)(*(int *)(data_020597fc + 4) + idx * 4 + 0x18) = value;
}
