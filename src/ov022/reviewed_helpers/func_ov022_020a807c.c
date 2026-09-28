extern void func_020a9314(void *sub);
void func_ov022_020a807c(char *node) {
    func_020a9314(*(void **)node);
    *(int *)(node + 0x40) += 1;
}
