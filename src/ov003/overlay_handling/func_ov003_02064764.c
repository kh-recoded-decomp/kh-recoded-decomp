/* Processes up to three typed record slots and forwards the first result. Evidence: Source implementation directly performs the described operations; see src/overlays/ov012/calls/func_ov012_0205b940.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/overlays/ov012/calls/func_ov012_0205b940.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
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
