extern void func_ov001_02067d80();
extern void func_ov001_0207ecc4();
extern void func_ov001_0206d95c();
extern void func_ov001_02087694();
extern void func_ov001_020668e4();
extern void func_020360a0();

void func_ov029_020ba86c(int mode)
{
    if (mode == 0) {
        func_ov001_02067d80(0x1000);
        func_ov001_0207ecc4(0x1000);
    }
    func_ov001_0206d95c(0x1000);
    if (mode == 0) {
        func_ov001_02087694(0x1000);
        func_ov001_020668e4();
    }
    func_020360a0(0x1000);
}
