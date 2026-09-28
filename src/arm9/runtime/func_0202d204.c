typedef void (*func_02025420_cb)(void *record, unsigned int callbackValueA, unsigned int callbackValueB);

extern func_02025420_cb data_02060574;

void func_0202d204(unsigned char *record) {
    data_02060574(record + *(int *)(record + 0x38),
                  (*(unsigned int *)(record + 0x2c) << 16) >> 13,
                  *(unsigned short *)(record + 0x30) << 3);
    *(unsigned short *)(record + 0x32) |= 1;
}
