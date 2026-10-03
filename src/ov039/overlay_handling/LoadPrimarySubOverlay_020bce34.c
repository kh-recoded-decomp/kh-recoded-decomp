typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayEntry data_ov039_020be92c[];
extern int func_02029f78(int processor, int overlay_id);

int LoadPrimarySubOverlay_020bce34(int index)
{
    int result = 0;

    data_ov039_020bea84[0] = index;
    if (index != -1) {
        result = func_02029f78(0, data_ov039_020be92c[index].overlayId);
    }
    return result;
}
