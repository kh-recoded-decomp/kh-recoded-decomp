void FS_SetArchiveProcedure_0200d09c(char *arc, void *proc, unsigned int flags) {
    if (flags == 0) {
        proc = 0;
    } else if (proc == 0) {
        flags = 0;
    }
    *(void **)(arc + 0x54) = proc;
    *(unsigned int *)(arc + 0x58) = flags;
}
