extern int func_02025dac(void *unknown_argument_a, void *unknown_argument_b);
extern void func_02063e94(int unknown_argument_x);

int func_ov003_02064764(void *context, char *record_slots) {
    int first_result = 0;
    if (*(short *)(record_slots + 0) == 2) {
        first_result = func_02025dac(context, record_slots);
    }
    if (*(short *)(record_slots + 8) == 2) {
        func_02025dac(context, record_slots + 8);
    }
    if (*(short *)(record_slots + 0x10) == 2) {
        func_02025dac(context, record_slots + 0x10);
    }
    func_02063e94(first_result);
    return 1;
}
