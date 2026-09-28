extern void func_01ffa37c();
void func_01ffa5b0(unsigned int *blocks)
{
    unsigned int flags = *blocks;
    if ((flags & 4) == 0) {
        if ((flags & 2) == 0)
            func_01ffa37c(0x19, blocks + 10, 0xc);
        else
            func_01ffa37c(0x1c, blocks + 0x13, 3);
    } else if ((flags & 2) == 0) {
        func_01ffa37c(0x1a, blocks + 10, 9);
    }
    if ((*blocks & 1) != 0)
        return;
    func_01ffa37c(0x1b, blocks + 1, 3);
}
