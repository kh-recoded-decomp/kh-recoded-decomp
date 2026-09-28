extern void func_01ff8830(void *dst, int val, unsigned int n);
extern int func_02023dbc(int a, int b);
extern void func_020524e8(void *p);
extern void func_0201288c(void *list, int a);
extern void func_020b9060(char *obj, int *tmpl);
extern void func_020b8f98(char *obj, char *data, int count);
extern unsigned char data_020603c8;
int InitializeResourceContainer_020b8bd4(char *param_1, int *param_2, int param_3, int param_4) {
    int budget;
    func_01ff8830(param_1, 0, 0x647c);
    *(unsigned short *)(param_1 + 0x6474) = 0xf0;
    switch (data_020603c8) {
        case 1: budget = 0x14; break;
        case 0: budget = 0x1e; break;
        case 2: budget = 0x3c; break;
    }
    *(int *)(param_1 + 0x6470) = func_02023dbc(0x3c000, budget);
    func_020524e8(param_1 + 0x6450);
    func_0201288c(param_1 + 0x6434, 0);
    if (param_2 != 0) {
        func_020b9060(param_1, param_2);
        if (param_2[5] != 0 && param_2[4] > 0) {
            func_020b8f98(param_1, (char *)param_2[5], param_2[4]);
        }
    }
    return 1;
}
