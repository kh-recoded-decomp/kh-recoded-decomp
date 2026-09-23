/* Validates a compact header and reads a byte from its referenced record unless flagged. Evidence: Source implementation directly performs the described operations; see src/auto/func_0202a1b8.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/auto/func_0202a1b8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
int ReadValidatedRecordByte_0202e804(unsigned char *header) {
    if (header == 0) return 0;
    if (!(*(unsigned short *)(header + 4) == 0xfeff
          && *(unsigned short *)(header + 0xc) == 0x10
          && *(unsigned short *)(header + 0xe) == 1)) {
        return 0;
    }
    {
        unsigned char *record = header + *(int *)(header + 0x10);
        return record[8] != 0 ? 0 : record[9];
    }
}
