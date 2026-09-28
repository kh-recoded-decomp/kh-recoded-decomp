/* Increments the generation byte for one alarm callback record.
 * Uncertainty: Alarm index validity is assumed by caller. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SNDi_IncAlarmId.c.
 * Original routine: SNDi_IncAlarmId. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* func_0200f508: bumps the id byte (+8) of alarm slot `n` (stride 0xc). */

extern unsigned char data_02059720;

void func_0200f508(int n) {
    ++*(unsigned char *)((int)&data_02059720 + n * 0xc + 8);
}
