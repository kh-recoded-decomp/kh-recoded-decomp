extern char data_02055774[];

void Callbacks_RunTableEntry_0202b3d4(int index, int arg1, int arg2, int arg3) {
    void (*callback)(int arg1, int arg2, int arg3);

    callback = *(void (**)(int, int, int))(data_02055774 + index * 0x18);
    if (callback != 0) {
        callback(arg1, arg2, arg3);
    }
}
