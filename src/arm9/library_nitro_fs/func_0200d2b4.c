extern int func_0200a0c4(void);
extern void FS_NotifyArchiveAsyncEnd(void *arc, int status);

void FS_CompleteArchiveAsyncRequest_0200d2b4(void *arc) {
    int status = func_0200a0c4() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(arc, status);
}
