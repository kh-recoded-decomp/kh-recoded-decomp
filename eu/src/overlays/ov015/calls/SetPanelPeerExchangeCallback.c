#include "nitro/types.h"

extern u8 gWhState[];
#define peerExchangeCallback (*(u32 *)(gWhState + 0x28))

void SetPanelPeerExchangeCallback(u32 callback)
{
    peerExchangeCallback = callback;
}
