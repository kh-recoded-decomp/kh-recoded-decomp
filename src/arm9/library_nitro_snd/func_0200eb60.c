/* Registers an alarm callback and submits a command containing alarm number, timing parameters and the callback generation ID.
 * Uncertainty: The timing arguments’ units are not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_SetupAlarm.c.
 * Original routine: SND_SetupAlarm. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Installs the alarm handler and pushes sound command 0x12 with the generation tag. */
extern int SNDi_SetAlarmHandler(int id, void *fn, void *arg);
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200eb60(int id, int tick, int period, void *fn, void *arg) {
    int gen = SNDi_SetAlarmHandler(id, fn, arg);
    PushCommand_impl(0x12, id, tick, period, gen);
}
