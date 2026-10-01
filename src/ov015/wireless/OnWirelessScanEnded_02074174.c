#include "nitro/types.h"

typedef struct WirelessCallback {
    u16 apiId;
    u16 errorCode;
} WirelessCallback;

typedef struct WirelessHelperState {
    u16 unk_00;
    u16 autoConnect;
    u8 pad_04[0x18];
    void *childKeyGenerator;
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern void func_020737c4(int state);
extern void func_020737d4(int errorCode);
extern BOOL func_020741ec(void);
extern BOOL func_02074288(void);

void OnWirelessScanEnded_02074174(WirelessCallback *callback)
{
    if (callback->errorCode != 0) {
        func_020737d4(callback->errorCode);
        return;
    }
    func_020737c4(1);
    if (!data_0207e980.autoConnect) {
        return;
    }
    data_0207e980.autoConnect = 0;
    if (data_0207e980.childKeyGenerator != NULL) {
        if (!func_020741ec()) {
            func_020737c4(9);
        }
    } else {
        if (!func_02074288()) {
            func_020737c4(9);
        }
    }
}
