/* Stores an archive procedure and flags, clearing both when either the procedure or flags is absent.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fs/auto/FS_SetArchiveProc.c.
 * Original routine: FS_SetArchiveProc. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Installs the archive hook, or clears both halves when either is missing. */
void FS_SetArchiveProcedure_0200d09c(char *arc, void *proc, unsigned int flags) {
    if (flags == 0) {
        proc = 0;
    } else if (proc == 0) {
        flags = 0;
    }
    *(void **)(arc + 0x54) = proc;
    *(unsigned int *)(arc + 0x58) = flags;
}
