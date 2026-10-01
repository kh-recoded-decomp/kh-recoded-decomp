#include "nitro/types.h"

typedef u16 (*ChildWepKeyGenerator)(u16 *wepKey, void *parentInfo);

typedef struct WirelessHelperState {
    u8 pad_00[0x1c];
    ChildWepKeyGenerator childKeyGenerator;
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern u16 data_0207e9e0[];
extern u8 data_0207eb60[];
extern void func_020737c4(int state);
extern void func_020737d4(int errorCode);
extern void func_02074250(void *callbackData);
extern int WM_SetWEPKey_0201228c(void (*callback)(void *), u16 wepMode, const u16 *wepKey);

BOOL SetChildWepKey_020741ec(void)
{
    int result;
    u16 wepMode;

    func_020737c4(3);
    wepMode = data_0207e980.childKeyGenerator(data_0207e9e0, data_0207eb60);
    result = WM_SetWEPKey_0201228c(func_02074250, wepMode, data_0207e9e0);
    if (result == 2) {
        return TRUE;
    }
    func_020737d4(result);
    func_020737c4(9);
    return FALSE;
}
