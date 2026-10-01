#include "nitro/types.h"

typedef struct WirelessCallback {
    u16 apiId;
    u16 errorCode;
} WirelessCallback;

typedef struct WirelessHelperState {
    u8 pad_00[0x18];
    void (*onReset)(WirelessCallback *callback);
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern void func_020737c4(int state);
extern void func_020737d4(int errorCode);

void OnWirelessResetDone_02074728(WirelessCallback *callback)
{
    if (callback->errorCode != 0) {
        func_020737c4(9);
        func_020737d4(callback->errorCode);
        return;
    }
    if (data_0207e980.onReset != NULL) {
        data_0207e980.onReset(callback);
    }
    func_020737c4(1);
}
