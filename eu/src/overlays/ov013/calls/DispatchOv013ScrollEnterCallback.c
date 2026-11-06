typedef struct {
    void (*handler)(void);
    unsigned char pad_04[8];
} PanelStateEntry;
extern int gOv013PanelGlobals;
extern PanelStateEntry gPanelScrollInitCallback[];

void DispatchOv013ScrollEnterCallback(void) {
    gPanelScrollInitCallback[*(signed char *)(gOv013PanelGlobals + 0xd258)].handler();
}
