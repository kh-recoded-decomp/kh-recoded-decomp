extern int SetWordAt0x588To1(int arg);
extern int data_020c34e0;
int ArmObject_020c0db4(void) {
    return SetWordAt0x588To1(*(int *)&data_020c34e0);
}
