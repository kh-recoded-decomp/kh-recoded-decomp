extern void func_02051dfc(int state);
extern void func_ov013_02071638(void);
extern int func_ov002_02066c78(int a, int b, int c, int d);
extern void func_0204d960(int a, int b, int c);
extern void func_ov002_02066a68(void);
extern void func_ov027_020b7dfc(int panel);
extern void func_ov027_020b8c58(int panel);
extern void func_0202a1c4(void *ptr);
extern int data_ov013_02074ce0;

void func_ov013_0206c760(void) {
    func_02051dfc(9);
    func_ov013_02071638();
    if (func_ov002_02066c78(5, 0, 0, 0) != 0) {
        func_0204d960(2, 0xd, 4);
    }
    func_ov002_02066a68();
    func_ov027_020b7dfc(data_ov013_02074ce0 + 0x304);
    func_ov027_020b7dfc(data_ov013_02074ce0 + 0x350);
    func_ov027_020b8c58(data_ov013_02074ce0 + 0x39c);
    func_ov027_020b8c58(data_ov013_02074ce0 + 0x6818);
    func_0202a1c4((void *)data_ov013_02074ce0);
}
