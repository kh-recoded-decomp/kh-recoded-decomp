#include "nitro/types.h"

extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern u32 func_02036810(u32 actorId);
extern u32 func_02036240(u32 actorId);
extern void PXI_Init_02088a88(u32 source, int *outX, int *outY);

BOOL IsPartnerAheadOfActor_02088a90(int actorId)
{
    u32 partner = ReadSessionPackedBits_02064574(0x3615, 8);
    BOOL locked = func_ov001_020645c8(0x3638);
    BOOL result;
    int leaderX;
    int leaderY;
    int partnerX;
    int partnerY;

    if ((actorId == -1 && partner != 0) || locked) {
        result = FALSE;
    } else if (actorId == -1 || partner == 0 || func_02036810((u16)actorId) == 0) {
        result = TRUE;
    } else {
        result = FALSE;
        PXI_Init_02088a88(func_02036240(0) + 0xa8, &leaderX, &leaderY);
        PXI_Init_02088a88(func_02036240((u16)partner) + 0xa8, &partnerX, &partnerY);
        if (actorId == 0) {
            if (leaderY > partnerY) {
                result = TRUE;
            }
        } else if (partnerY > leaderY) {
            result = TRUE;
        }
    }
    return result;
}
