typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayEntry data_ov039_020be8cc[];
extern int func_02029f78(int processor, int overlay_id);

int UnloadSecondarySubOverlay_020bcf88(void)
{
    int result = 1;
    int index = data_ov039_020bea84[1];

    if (index != -1) {
        result = func_02029f78(0, data_ov039_020be8cc[index].overlayId);
        data_ov039_020bea84[1] = -1;
    }
    return result;
}
