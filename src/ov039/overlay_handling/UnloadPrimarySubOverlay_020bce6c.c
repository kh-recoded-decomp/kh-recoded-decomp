typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayEntry data_ov039_020be92c[];
extern int func_02029f98(int processor, int overlay_id);

int UnloadPrimarySubOverlay_020bce6c(void)
{
    int result = 1;
    int index = data_ov039_020bea84[0];

    if (index != -1) {
        result = func_02029f98(0, data_ov039_020be92c[index].overlayId);
        data_ov039_020bea84[0] = -1;
    }
    return result;
}
