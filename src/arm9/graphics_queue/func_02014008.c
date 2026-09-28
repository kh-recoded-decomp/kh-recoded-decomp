extern int *func_02013f74(int *queueState);
extern int func_02013f94(int *queueState);
extern void func_02013ee4(int *command, int underBudget);
extern void DC_StoreAll(void);
extern char data_0205a8d0;
extern char data_0205a8d0_budget;

void func_02014008(void) {
    int *queueState = (int *)&data_0205a8d0;
    int *command;
    unsigned char underBudget;

    command = func_02013f74(queueState);
    underBudget = *(unsigned int *)((char *)&data_0205a8d0_budget + 0x10) < 0x2400;
    if (underBudget == 0) {
        DC_StoreAll();
    }
    if (func_02013f94(queueState) != 0) {
        do {
            func_02013ee4(command, underBudget);
            *(int *)((char *)queueState + 0x10) -= command[3];
            command = func_02013f74(queueState);
        } while (func_02013f94(queueState) != 0);
    }
}
