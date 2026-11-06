#include "nitro/types.h"

typedef u16 (*ChildWepKeyGenerator)(u16 *wepKey, void *parentInfo);

typedef struct WirelessHelperState {
    u8 pad_00[52];
    ChildWepKeyGenerator childKeyGenerator;
} WirelessHelperState;

extern WirelessHelperState gWhState;
extern u16 gWirelessWepKeyStorage[];
extern u8 gWirelessParentParamStorage[];
extern void WH_ChangeSysState(int state);
extern void WH_SetError(int errorCode);
extern void WH_OnParentWepKeySet(void *callbackData);
extern int WM_SetWEPKey(void (*callback)(void *), u16 wepMode, const u16 *wepKey);

BOOL WH_RequestParentWepKey(void)
{
    int result;
    u16 wepMode;

    WH_ChangeSysState(3);
    wepMode = gWhState.childKeyGenerator(gWirelessWepKeyStorage, gWirelessParentParamStorage);
    result = WM_SetWEPKey(WH_OnParentWepKeySet, wepMode, gWirelessWepKeyStorage);
    if (result == 2) {
        return TRUE;
    }
    WH_SetError(result);
    WH_ChangeSysState(9);
    return FALSE;
}
