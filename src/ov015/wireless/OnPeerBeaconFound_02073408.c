#include "nitro/types.h"

typedef struct ConnectState {
    u8 pad_00[0x08];
    u8 peerCard[0x5e];
    u8 peerMac[6];
    u8 pad_6c[0xd];
    u8 lowFlag : 1;
    u8 exchangeStarted : 1;
    u8 scanPending : 1;
    u8 peerSeen : 1;
    u8 midFlag : 1;
    u8 peerKnown : 1;
    u8 peerReady : 1;
    u8 highFlag : 1;
    u8 exchangeStep : 2;
    u8 exchangeLocked : 1;
    u8 otherFlags : 5;
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern BOOL IsKnownMacAddress_02072490(u8 *macAddress);
extern u32 func_0202a9d0(u32 range);
extern void MIi_CpuFill8_01ff8830(void *dest, u8 data, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);

void OnPeerBeaconFound_02073408(u8 *macAddress)
{
    if (!data_ov015_0207e964->scanPending) {
        return;
    }
    data_ov015_0207e964->peerSeen = 1;
    if (data_ov015_0207e964->peerKnown) {
        return;
    }
    if (data_ov015_0207e964->exchangeLocked) {
        return;
    }
    if (IsKnownMacAddress_02072490(macAddress)) {
        return;
    }
    data_ov015_0207e964->scanPending = 0;
    data_ov015_0207e964->exchangeStarted = 1;
    data_ov015_0207e964->exchangeStep = 1;
    if (func_0202a9d0(750) != 100) {
        return;
    }
    data_ov015_0207e964->peerKnown = 1;
    MIi_CpuFill8_01ff8830(data_ov015_0207e964->peerCard, 0, 0x70);
    func_01ff89a8(macAddress, data_ov015_0207e964->peerMac, 6);
    data_ov015_0207e964->peerReady = 1;
}
