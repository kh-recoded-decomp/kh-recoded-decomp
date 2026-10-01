#include "nitro/types.h"

typedef struct StageActor {
    u8 pad_000[0x28a];
    u16 lowFlags : 10;
    u16 cellState : 4;
    u16 highFlags : 2;
    u16 lowBits : 3;
    u16 cellRow : 4;
    u16 cellColumn : 4;
    u16 upperBits : 5;
} StageActor;

void SetActorGridCell_0209191c(StageActor *actor, u16 column, u16 row)
{
    actor->cellColumn = (u16)(column + 1);
    actor->cellRow = (u16)(row + 1);
    actor->cellState = 0;
}
