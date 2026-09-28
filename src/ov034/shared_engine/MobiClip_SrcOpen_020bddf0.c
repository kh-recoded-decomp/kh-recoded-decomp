extern int InstantiateClass(void *desc, int arg);
extern int data_020be934;
extern int data_020be920;

void MobiClip_SrcOpen_020bddf0(int arg) {
    data_020be920 = InstantiateClass(&data_020be934, arg);
}
