typedef void (*SubOverlayCallback)(int arg);

typedef struct {
    SubOverlayCallback init;
    SubOverlayCallback exit;
} SubOverlayCallbacks;

typedef struct {
    SubOverlayCallbacks *callbacks;
    int unused;
} SubOverlayHandlerEntry;

typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020bea84[2];
extern SubOverlayHandlerEntry data_ov039_020be8d0[];
extern SubOverlayEntry data_ov039_020be8cc[];
extern void func_02029f98(int processor, int overlay_id);

void CloseSecondarySubOverlay_020bd00c(int arg)
{
    if (data_ov039_020bea84[1] == -1) {
        return;
    }
    data_ov039_020be8d0[data_ov039_020bea84[1]].callbacks->exit(arg);
    func_02029f98(0, data_ov039_020be8cc[data_ov039_020bea84[1]].overlayId);
}
