extern void func_020b7aa0(int self);
extern void func_020b7c30(int self);
struct pend { unsigned char b0 : 1; };
void func_ov027_020b7dd4(int param_1) {
    func_020b7aa0(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_020b7c30(param_1);
}
