extern void func_0200edc8(void);
extern void func_0200eddc(void);
extern void DC_StoreRange(void *p, unsigned int len);

void func_0200fa9c(char *table, int slot, void *addr) {
    func_0200edc8();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    func_0200eddc();
}
