typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayEntry data_ov039_020be8cc[];
extern int func_02029f78(int processor, int overlay_id);

int LoadSecondarySubOverlay_020bcf50(int index)
{
    int result = 0;

    data_ov039_020bea84[1] = index;
    if (index != -1) {
        result = func_02029f78(0, data_ov039_020be8cc[index].overlayId);
    }
    return result;
}
