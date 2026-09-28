extern void OS_DisableIrqMask();

extern struct {
    unsigned short state;
    unsigned short pad;
    int field_4;
    int field_8;
    int field_c;
    int field_10;
} data_02056eb0;

void initialize_irq_backed_timer_state_02004528(void) {
    if (data_02056eb0.state != 0) return;
    data_02056eb0.state = 1;
    data_02056eb0.field_c = 0;
    data_02056eb0.field_10 = 0;
    OS_DisableIrqMask(4);
    data_02056eb0.field_8 = 0;
    data_02056eb0.field_4 = 0;
}
