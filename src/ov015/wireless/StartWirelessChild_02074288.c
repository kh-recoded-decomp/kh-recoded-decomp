#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x1c];
    void *childKeyGenerator;
    u8 pad_20[0x30];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern u8 data_0207eb60[];
extern u8 data_0207e9f4[];
extern void func_020737c4(int state);
extern void func_020737d4(int errorCode);
extern void func_0207431c(void *callbackData);
extern int WM_StartConnectEx_02011964(void (*callback)(void *), const void *parentInfo, const u8 *ssid, BOOL powerSave, const u16 authMode);

BOOL StartWirelessChild_02074288(void)
{
    int result;

    if (data_0207e980.sysState == 4 || (u32)data_0207e980.sysState == 6 || data_0207e980.sysState == 5) {
        return TRUE;
    }
    func_020737c4(3);
    result = WM_StartConnectEx_02011964(func_0207431c, data_0207eb60, data_0207e9f4, TRUE,
                                        (u16)(data_0207e980.childKeyGenerator != NULL ? 1 : 0));
    if (result != 2) {
        func_020737d4(result);
        return FALSE;
    }
    return TRUE;
}
