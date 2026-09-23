/* Initializes timer 0, its interrupt callback, and associated shared timer state once.
 * Evidence: Timer register writes, reserved timer setup, IRQ registration, and active guard in source.
 * Uncertainty: Timer state fields beyond active are only identified by their reset behavior.
 * Source: src/calls/func_020030e4.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void OSi_SetTimerReserved(unsigned short timer);
extern void OS_SetIrqFunction(unsigned int mask, void (*callback)(void));
extern unsigned int OS_EnableIrqMask(unsigned int mask);
extern void func_02003f6c(void);

typedef struct {
    unsigned short active;
    unsigned short _pad;
    int field_4;
    int field_8;
    int field_c;
} Data_02044664;

extern Data_02044664 data_02056e94;

#define TM0CNT_L (*(volatile unsigned short *)0x04000100)
#define TM0CNT_H (*(volatile unsigned short *)0x04000102)

void initialize_frame_timer_02003eec(void)
{
    if (data_02056e94.active != 0)
        return;

    data_02056e94.active = 1;
    OSi_SetTimerReserved(0);
    data_02056e94.field_8 = 0;
    data_02056e94.field_c = 0;
    TM0CNT_H = 0;
    TM0CNT_L = 0;
    TM0CNT_H = 0xC1;
    OS_SetIrqFunction(8, func_02003f6c);
    OS_EnableIrqMask(8);
    data_02056e94.field_4 = 0;
}
