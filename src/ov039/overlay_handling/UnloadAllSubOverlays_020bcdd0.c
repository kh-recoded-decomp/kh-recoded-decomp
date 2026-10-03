typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayEntry data_ov039_020be92c[];
extern SubOverlayEntry data_ov039_020be8cc[];
extern void func_02029f98(int processor, int overlay_id);

void UnloadAllSubOverlays_020bcdd0(void)
{
    if (data_ov039_020bea84[0] != -1) {
        func_02029f98(0, data_ov039_020be92c[data_ov039_020bea84[0]].overlayId);
        data_ov039_020bea84[0] = -1;
    }
    if (data_ov039_020bea84[1] != -1) {
        func_02029f98(0, data_ov039_020be8cc[data_ov039_020bea84[1]].overlayId);
        data_ov039_020bea84[1] = -1;
    }
}
