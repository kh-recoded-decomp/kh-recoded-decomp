extern void DestroyTaskObjectWrapper();
extern int data_ov022_020b7c00;

void func_ov022_020a7834(void) {
    int v = data_ov022_020b7c00;
    if (v == -1) {
        return;
    }
    DestroyTaskObjectWrapper(v);
}
