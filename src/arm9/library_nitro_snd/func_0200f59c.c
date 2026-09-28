extern void DC_InvalidateRange(void *p, unsigned int len);
extern int *data_02059780;

int func_0200f59c(void) {
    DC_InvalidateRange(data_02059780 + 1, 4);
    return data_02059780[1];
}
