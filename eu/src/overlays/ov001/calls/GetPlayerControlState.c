#include "src/overlays/ov001/EventContext.h"

PlayerControlState *GetPlayerControlState(u32 playerIndex)
{
    PlayerControlSlot *players = (PlayerControlSlot *)((u8 *)gEventContext + sizeof(gEventContext->header));
    PlayerControlSlot *slot = players + playerIndex;

    return (PlayerControlState *)((u8 *)slot + sizeof(slot->pad_00));
}
