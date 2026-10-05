#include "nitro/types.h"

typedef struct ActorMotion {
    u32 timerA;
    u32 timerB;
    u32 timerC;
    u8 pad_0c[0xbc];
    u32 stateFlags : 31;
    u32 stateHighBit : 1;
    u8 pad_cc[0x1a];
    u16 renderLow : 9;
    u16 renderBit9 : 1;
    u16 renderHigh : 6;
} ActorMotion;

typedef struct StageActor {
    u8 pad_00[4];
    u16 statusLow : 2;
    u16 statusBit2 : 1;
    u16 statusMid : 4;
    u16 statusBit7 : 1;
    u16 statusBit8 : 1;
    u16 statusBit9 : 1;
    u16 statusBit10 : 1;
    u16 statusBit11 : 1;
    u16 statusBit12 : 1;
    u16 statusBit13 : 1;
    u16 statusBit14 : 1;
    u16 statusBit15 : 1;
    u16 modeBit0 : 1;
    u16 modeBit1 : 1;
    u16 modeBit2 : 1;
    u16 modeBit3 : 1;
    u16 modeBit4 : 1;
    u16 modeBit5 : 1;
    u16 modeBit6 : 1;
    u16 modeMid : 3;
    u16 modeBit10 : 1;
    u16 modeHigh : 5;
    u8 pad_08[4];
    u8 linkState;
    u8 pad_0d[3];
    u16 linkedActorId;
    u8 pad_12[0x192];
    ActorMotion motion;
} StageActor;

extern StageActor *GetStageActor_0209c040(int id);
extern StageActor *GetLinkedStageActor_0209c2f0(StageActor *actor);

void ResetStageActorFlags_02093188(StageActor *leader)
{
    StageActor *actor;

    leader->linkState = 0;
    leader->motion.timerA = 0;
    leader->motion.timerB = 0;
    leader->motion.timerC = 0;
    leader->statusBit2 = 0;
    leader->modeBit6 = 0;
    leader->statusBit7 = 0;
    leader->statusBit8 = 0;
    leader->statusBit9 = 0;
    leader->statusBit10 = 0;
    leader->statusBit11 = 0;
    leader->statusBit12 = 0;
    leader->statusBit14 = 0;
    leader->statusBit15 = 0;
    leader->modeBit0 = 0;
    leader->modeBit1 = 0;
    leader->modeBit2 = 0;
    leader->modeBit3 = 0;
    leader->modeBit4 = 0;
    leader->modeBit5 = 0;
    leader->modeBit10 = 0;
    if (leader->linkedActorId != 0) {
        for (actor = GetStageActor_0209c040((s16)leader->linkedActorId); actor != NULL;
             actor = GetLinkedStageActor_0209c2f0(actor)) {
            actor->motion.renderBit9 = 0;
            actor->motion.stateFlags &= ~2;
            actor->motion.stateFlags &= ~0x10;
            actor->motion.stateFlags &= ~0x100;
            actor->motion.stateFlags &= ~0x200;
        }
    }
}
