#include "nitro/types.h"

typedef struct {
    u8 unk_00[8];
    u32 handle;
    u32 unk_0C;
    char name[0x80];
    u32 mode;
} PanelRequest;

typedef struct {
    void (*submit)(PanelRequest *request);
    u32 unk_04;
    void (*finish)(void);
} PanelCallbacks;

typedef struct {
    u8 pad_00[0x668c];
    u32 handle;
    u8 pad_6690[4];
    PanelCallbacks callbacks;
} Panel;

extern const char data_ov000_02063938[];
extern void OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void func_ov022_020a787c(PanelCallbacks *callbacks);

void SubmitNumberedPanelRequest_02061f54(Panel *panel, BOOL useAltMode, int number)
{
    PanelRequest request;

    request.handle = panel->handle;
    request.unk_0C = 1;
    request.mode = useAltMode ? 2 : 1;
    OS_SPrintf_02002428(request.name, data_ov000_02063938, number);
    func_ov022_020a787c(&panel->callbacks);
    panel->callbacks.submit(&request);
    panel->callbacks.finish();
}
