/* Calls the registered callback with a payload address and two values decoded from a record, then marks the record flag.
 * Evidence: Callback pointer, field offsets, shifts, and flag bit in source.
 * Uncertainty: Payload format and units remain unknown.
 * Source: src/calls/func_02025420.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef void (*func_02025420_cb)(void *record, unsigned int callbackValueA, unsigned int callbackValueB);

extern func_02025420_cb data_02060574;

void func_0202d204(unsigned char *record) {
    data_02060574(record + *(int *)(record + 0x38),
                  (*(unsigned int *)(record + 0x2c) << 16) >> 13,
                  *(unsigned short *)(record + 0x30) << 3);
    *(unsigned short *)(record + 0x32) |= 1;
}
