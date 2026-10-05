int MI_SwapWord_020056cc(int value, int *ptr)
{
    int old;
    __asm
    {
        swp old, value, [ptr]
    }
    return old;
}
