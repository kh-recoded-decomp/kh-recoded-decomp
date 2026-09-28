extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ed24(int player, unsigned int trackMask, int param, int value, int immediate) {
    PushCommand_impl(7, player | (immediate << 24), trackMask, param, value);
}
