#include "nitro/types.h"

extern void OnPeerBeaconFound(void);
extern void BeginPeerCardExchange(void);
extern void WH_Initialize(void);
extern void SetWirelessSessionParam(u32 value);
extern void SetPanelPendingValue(u32 value);
extern void SetPanelPeerExchangeCallback(u32 callback);

void InitPeerWirelessSession(void)
{
    WH_Initialize();
    SetWirelessSessionParam(0x800558);
    SetPanelPendingValue((u32)OnPeerBeaconFound);
    SetPanelPeerExchangeCallback((u32)BeginPeerCardExchange);
}
