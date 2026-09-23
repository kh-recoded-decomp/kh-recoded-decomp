/* Settles an asynchronous read, seeks a file, and updates the cursor position on success. Evidence: Source implementation directly performs the described operations; see src/overlays/ov024/calls/func_ov024_02085e8c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov024/calls/func_ov024_02085e8c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void FS_WaitAsync(int *file, int unknown_argument_a, void *wait_buffer, int wait_flags);
extern int  FS_SeekFile(int file, int target_position, int whence);

int SeekBitstreamCursor_020aa168(int bitstream_cursor, int target_position, void *wait_buffer, int wait_flags) {
    if (*(unsigned char *)(bitstream_cursor + 0x10) == 1) {
        FS_WaitAsync(*(int **)(bitstream_cursor + 0xc), target_position, wait_buffer, wait_flags);
        *(unsigned char *)(bitstream_cursor + 0x10) = 0;
    }
    if (FS_SeekFile(*(int *)(bitstream_cursor + 0xc), target_position, 0) == 0) {
        return 0;
    }
    *(int *)(bitstream_cursor + 8) = target_position;
    return 1;
}
