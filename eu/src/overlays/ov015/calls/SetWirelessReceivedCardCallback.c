#include "nitro/types.h"

/* Canonical 28-byte BSS prefix; defined in Bss_ov015_0207e960.c.
 * Its first native word points to the connection work. Other words are opaque. */
extern u32 data_ov015_0207e964[7];

/* StartPlayerCardSharing registers AddReceivedPlayerCard here.
 * InvokePanelCallback passes the received profile to the slot at +0x90.
 * callbackWord is a DS function-pointer encoding, not a host address.
 * See docs/PANEL_WIRELESS_CALLBACK_CONTRACTS.md. */
void SetWirelessReceivedCardCallback(s32 callbackWord)
{
    u8 *connectionWork = (u8 *)data_ov015_0207e964[0];
    *(s32 *)(connectionWork + 0x90) = callbackWord;
}
