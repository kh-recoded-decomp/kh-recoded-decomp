extern int func_0202c48c(int data, int kind);
extern void func_020b8f5c(int self, int obj, int arg);
extern void func_0202a1c4(void *obj);
void func_ov027_020b8f98(int param_1, int param_2, int param_3) {
    int obj = func_0202c48c(param_2, 0xe);
    func_020b8f5c(param_1, obj, param_3);
    if (obj != 0) func_0202a1c4((void *)obj);
}
