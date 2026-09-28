extern void func_0202a638(int arg);

extern int data_0209eab0;

void ReleaseServiceInstance_02068e64(void) {
    if (data_0209eab0 == -1) return;
    func_0202a638(data_0209eab0);
    data_0209eab0 = -1;
}
