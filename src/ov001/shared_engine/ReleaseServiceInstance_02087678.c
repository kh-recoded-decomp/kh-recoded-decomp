extern void func_0209b8c4(int arg);

extern int data_0209f2c8;

void ReleaseServiceInstance_02087678(void) {
    if (data_0209f2c8 == -1) return;
    func_0209b8c4(data_0209f2c8);
    data_0209f2c8 = -1;
}
