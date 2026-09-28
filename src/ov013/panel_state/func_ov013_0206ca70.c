typedef struct {
    void (*handler)(void);
    unsigned char pad_04[8];
} PanelStateEntry;
extern int data_ov013_02074ce0;
extern PanelStateEntry g_panelStateTable_02074b38[];

void func_ov013_0206ca70(void) {
    g_panelStateTable_02074b38[*(signed char *)(data_ov013_02074ce0 + 0xd258)].handler();
}
