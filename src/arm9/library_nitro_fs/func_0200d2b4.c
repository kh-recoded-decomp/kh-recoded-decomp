/* Converts a helper result into status zero or five and notifies an archive that its asynchronous request ended.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fs/calls/FSi_OnRomReadDone.c.
 * Original routine: FSi_OnRomReadDone. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Ends the asynchronous archive command with status 5 when the ROM thread is still
 * available, otherwise with 0. */
extern int func_0200a0c4(void);
extern void FS_NotifyArchiveAsyncEnd(void *arc, int status);

void FS_CompleteArchiveAsyncRequest_0200d2b4(void *arc) {
    int status = func_0200a0c4() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(arc, status);
}
