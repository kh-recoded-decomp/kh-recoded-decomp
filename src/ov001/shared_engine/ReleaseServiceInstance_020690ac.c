extern void func_0202a638(int arg);

extern int data_0209eac8;

void ReleaseServiceInstance_020690ac(void) {
    if (data_0209eac8 == -1) return;
    func_0202a638(data_0209eac8);
    data_0209eac8 = -1;
}
