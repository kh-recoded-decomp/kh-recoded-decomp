/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_01ffa37c(unsigned int cmd, const void *src, unsigned int words);

struct Gfx0201571c {
    unsigned int cmd;       
    char _4[0xd0];
    unsigned int field_d4;  
};

extern struct Gfx0201571c data_0205a924;

void func_02019188(void)
{
    unsigned int *p = (unsigned int *)&data_0205a924;
    func_01ffa37c(*p, p + 1, 0x34);
    data_0205a924.field_d4 &= ~1u;
    data_0205a924.field_d4 &= ~2u;
}
