extern int SNDi_SetAlarmHandler(int id, void *fn, void *arg);
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200eb60(int id, int tick, int period, void *fn, void *arg) {
    int gen = SNDi_SetAlarmHandler(id, fn, arg);
    PushCommand_impl(0x12, id, tick, period, gen);
}
