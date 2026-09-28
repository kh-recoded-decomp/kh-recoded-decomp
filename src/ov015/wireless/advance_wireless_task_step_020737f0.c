extern void func_020737c4(int state);
extern int func_02011738(void *fn, void *arg);
extern void func_020737d4(void);
extern void func_02073830(void);
extern int data_0207ea20;

int advance_wireless_task_step_020737f0(void) {
    func_020737c4(3);
    if (func_02011738((void *)&func_02073830, &data_0207ea20) == 2) {
        return 1;
    }
    func_020737d4();
    func_020737c4(9);
    return 0;
}
