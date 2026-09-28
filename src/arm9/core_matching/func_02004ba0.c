/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_02004938(void);
extern void func_0200494c(int state);
extern int func_02004b64(unsigned int value);
extern unsigned int data_02056ec8;
extern unsigned short data_02056ecc[];

void func_02004ba0(unsigned int mask, unsigned short owner)
{
    unsigned int mine;
    int enabled = func_02004938();
    int bit;
    unsigned int clear;

    mine = mask & data_02056ec8 & 0x1ff;
    for (;;) {
        bit = 0x1f - func_02004b64(mine);
        if (bit < 0) {
            break;
        }
        clear = ~(1u << bit);
        mine &= clear;
        if (owner == data_02056ecc[bit]) {
            data_02056ecc[bit] = 0;
            data_02056ec8 &= clear;
        }
    }
    func_0200494c(enabled);
}
