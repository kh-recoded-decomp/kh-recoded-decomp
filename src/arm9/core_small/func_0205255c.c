/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern long long func_02003fd4(void);

struct obj {
    int _pad[4];
    long long value;
    unsigned flag0 : 1;
    unsigned flag1 : 1;
    unsigned flag2 : 1;
};

void func_0205255c(struct obj *o) {
    o->value = func_02003fd4();
    o->flag0 = 1;
    o->flag1 = 0;
    o->flag2 = 0;
}
