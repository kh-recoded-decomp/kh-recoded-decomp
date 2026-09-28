extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_02057c50;

int func_0200f304(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_02057c50;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}
