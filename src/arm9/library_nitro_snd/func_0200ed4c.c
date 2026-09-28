extern char *SND_AllocCommand(int wait);
extern void func_0200f048(char *cmd);

void func_0200ed4c(int cmd, int a, int b, int c, int d) {
    char *slot = SND_AllocCommand(1);
    if (slot == 0) {
        return;
    }
    *(int *)(slot + 4) = cmd;
    *(int *)(slot + 8) = a;
    *(int *)(slot + 0xc) = b;
    *(int *)(slot + 0x10) = c;
    *(int *)(slot + 0x14) = d;
    func_0200f048(slot);
}
