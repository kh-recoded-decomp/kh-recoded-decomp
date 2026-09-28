extern int InstantiateClass(void *classDesc, int *params);

extern int data_0209eab0;
extern char data_0209eab4[];

void CreateRootObject_02068d5c(int param) {
    int params[1];

    params[0] = param;
    data_0209eab0 = InstantiateClass(data_0209eab4, params);
}
