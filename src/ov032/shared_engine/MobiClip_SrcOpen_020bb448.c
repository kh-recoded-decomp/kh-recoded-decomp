extern int InstantiateClass(void *desc, int arg);
extern int data_020bffc4;
extern int data_020bffc0;

void MobiClip_SrcOpen_020bb448(int arg) {
    data_020bffc0 = InstantiateClass(&data_020bffc4, arg);
}
