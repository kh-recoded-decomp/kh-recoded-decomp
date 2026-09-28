/* Target-derived C from the Ghidra body at arm9:func_0200b178. */
extern int func_02004938(void);
extern void func_0200494c(int state);
extern void func_02002af8(void *queue);
extern void func_0200a200(void *file);
extern int func_0200a67c(void *archive, int arg);
extern void func_0200a828(void);

void func_0200b178(void *context, int result)
{
    char *file = *(char **)((char *)context + 8);
    unsigned int *status = (unsigned int *)(file + 0xc);
    int state;

    if ((*status & 4) != 0) {
        state = func_02004938();
        *status |= 8;
        *(int *)(file + 0x14) = result;
        func_02002af8(file + 0x18);
        func_0200494c(state);
        return;
    }

    func_0200a200(file);
    if (func_0200a67c(context, 1) == 0) {
        return;
    }
    func_0200a828();
}
