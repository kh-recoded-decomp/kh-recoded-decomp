extern void func_0202a1c4();
extern int data_0206c46c;

void func_ov002_02066a68(void) {
    int p = *(int *)&data_0206c46c;
    if (p == 0) {
        return;
    }
    func_0202a1c4(p);
    data_0206c46c = 0;
}
