/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int data_02057c50[];

int func_0200f288(void) {
    int mask;
    int result;
    mask = OS_DisableInterrupts();
    if (data_02057c50[2] == 0) {
        result = data_02057c50[1];
    } else {
        result = data_02057c50[8];
    }
    OS_RestoreInterrupts(mask);
    return result;
}
