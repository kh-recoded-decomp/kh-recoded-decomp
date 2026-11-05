#include "nitro/types.h"

extern u32 AddSessionCounter();
extern u32 AddToSelectionCounters_020c7564();
extern u32 ApplyItemScreenThresholdRankBonus();
extern u32 ClearItemScreenSessionStateWordsThunk();
extern void QueueAndPlaySound(int soundId, int index);

void ApplyItemScreenItemReward(u32 reward)

{
  switch(reward) {
  case 0xb7:
    AddToSelectionCounters_020c7564(0x1e);
    AddSessionCounter(5,1);
    QueueAndPlaySound(0xb2,0);
    return;
  case 0xb8:
    AddToSelectionCounters_020c7564(0x32);
    AddSessionCounter(5,1);
    QueueAndPlaySound(0xb3,0);
    return;
  case 0xbb:
    ClearItemScreenSessionStateWordsThunk();
    AddSessionCounter(5,1);
    QueueAndPlaySound(0xb6,0);
    return;
  case 0xb9:
    ApplyItemScreenThresholdRankBonus(1);
    QueueAndPlaySound(0xb4,0);
    return;
  case 0xba:
    ApplyItemScreenThresholdRankBonus(2);
    QueueAndPlaySound(0xb5,0);
    return;
  case 0xbc:
    AddToSelectionCounters_020c7564(1000);
    ClearItemScreenSessionStateWordsThunk();
    AddSessionCounter(5,1);
    QueueAndPlaySound(0xb7,0);
    return;
  case 0xbd:
    ApplyItemScreenThresholdRankBonus(4);
    AddToSelectionCounters_020c7564(1000);
    ClearItemScreenSessionStateWordsThunk();
    AddSessionCounter(5,1);
    AddSessionCounter(0x12,1);
    QueueAndPlaySound(0xb8,0);
  }
  return;
}
