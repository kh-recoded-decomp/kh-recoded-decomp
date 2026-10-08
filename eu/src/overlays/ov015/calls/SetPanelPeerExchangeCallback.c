#include "nitro/types.h"

extern u8 data_ov015_0207e980[];
#define peerExchangeCallback (*(u32 *)(data_ov015_0207e980 + 0x28))

void SetPanelPeerExchangeCallback(u32 callback)
{
    peerExchangeCallback = callback;
}
