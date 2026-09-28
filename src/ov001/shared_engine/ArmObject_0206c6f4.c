extern int SetWordAt0x588To1(int arg);
extern int data_020a0488;
int ArmObject_0206c6f4(void) {
    return SetWordAt0x588To1(*(int *)&data_020a0488);
}
