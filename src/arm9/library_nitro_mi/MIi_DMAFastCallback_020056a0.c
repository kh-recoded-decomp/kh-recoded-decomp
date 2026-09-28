extern int data_02056ee8;

void MIi_DMAFastCallback_020056a0(void) {
    void (*cb)(int);
    int arg;

    data_02056ee8 = 0;
    cb = *(void (**)(int))((int)&data_02056ee8 + 0x10);
    arg = *(int *)((int)&data_02056ee8 + 0x14);
    if (cb != 0) {
        cb(arg);
    }
}
