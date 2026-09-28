extern int Archive_LoadFile();
extern void StreamReader_InitU16();

int func_02001458(int *arg0, char *arg1, int arg2, int arg3) {
    arg0[2] = Archive_LoadFile(arg1, 0xe, arg2, arg3);
    StreamReader_InitU16(arg0, (int *)arg0[2]);
    return 1;
}
