extern int StackAlloc_FreeIfSet();

int StackAlloc_FreeIfSetB_02021978(int a) {
    if (a) StackAlloc_FreeIfSet(a);
}
