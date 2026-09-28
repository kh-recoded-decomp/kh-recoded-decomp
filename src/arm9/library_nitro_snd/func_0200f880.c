extern void func_0200edc8(void);
extern void func_0200eddc(void);
extern void DC_StoreRange(void *p, unsigned int len);

void func_0200f880(int **owner) {
    int *node;
    int zero;
    int len;
    int *next;
    func_0200edc8();
    node = (int *)owner[6];
    if (node != 0) {
        zero = 0;
        len = 8;
        do {
            next = (int *)node[1];
            node[0] = zero;
            node[1] = zero;
            DC_StoreRange(node, len);
            node = next;
        } while (next != 0);
    }
    func_0200eddc();
}
