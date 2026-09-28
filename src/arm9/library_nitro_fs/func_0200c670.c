/* Copies words 12, 13 and 14 of a record into words 9/11, 10 and 8 respectively, then returns zero.
 * Uncertainty: The record/tag meaning and its game-facing role remain unknown. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fs/auto/FSi_OpenFileDirectCommand.c.
 * Original routine: FSi_OpenFileDirectCommand. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
int func_0200c670(int *param)
{
    param[9] = param[12];
    param[11] = param[12];
    param[10] = param[13];
    param[8] = param[14];
    return 0;
}
