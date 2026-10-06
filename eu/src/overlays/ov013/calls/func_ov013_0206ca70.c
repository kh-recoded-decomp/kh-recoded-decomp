typedef struct {
    void (*handler)(void);
    unsigned char pad_04[8];
} PanelStateEntry;
extern int data_ov013_02074ce0;
extern PanelStateEntry gPanelScrollInitCallback[];

void func_ov013_0206ca70(void) {
    gPanelScrollInitCallback[*(signed char *)(data_ov013_02074ce0 + 0xd258)].handler();
}
