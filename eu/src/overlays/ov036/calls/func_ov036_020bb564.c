#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;
extern unsigned int StepActorSlotMove();
extern unsigned int UpdateSpriteShake();
extern unsigned int StepActorSlotAlphaFade();

void func_ov036_020bb564(int index) {
  int record;

  record = index * 0x9c + *(int *)(data_ov036_020c3940.value + 0x1090);
  if ((*(u16 *)(record + 0x88) & 1) != 0) {
    StepActorSlotMove(record);
  }
  if ((*(u16 *)(record + 0x88) & 2) != 0) {
    UpdateSpriteShake(record);
  }
  if ((*(u16 *)(record + 0x88) & 4) == 0) {
    return;
  }
  StepActorSlotAlphaFade(record);
}
