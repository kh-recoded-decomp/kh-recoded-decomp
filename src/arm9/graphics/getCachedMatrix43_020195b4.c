extern void func_020193b8(void *sourceMatrix, void *cachedMatrix);
extern struct { char padding[0xd4]; int flags; } data_0205a924;
extern char data_0205a92c[];
extern char data_0205aabc[];

void *getCachedMatrix43_020195b4(void)
{
    if ((data_0205a924.flags & 0x10) == 0) {
        func_020193b8(data_0205a92c, data_0205aabc);
        data_0205a924.flags |= 0x10;
    }
    return data_0205aabc;
}
