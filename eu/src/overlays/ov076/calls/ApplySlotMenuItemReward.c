#include "nitro/types.h"

extern u32 AddSessionCounter();
extern u32 AddToSelectionCounters_020ca530();
extern u32 ApplySlotMenuThresholdRankBonus();
extern u32 ClearSlotMenuSessionStateWordsThunk();
extern u32 LoadOverlaySync_020ca630();

void ApplySlotMenuItemReward(u32 reward)

{
  switch(reward) {
  case 0xb7:
    AddToSelectionCounters_020ca530(0x1e);
    AddSessionCounter(5,1);
    LoadOverlaySync_020ca630(0xb2,0);
    return;
  case 0xb8:
    AddToSelectionCounters_020ca530(0x32);
    AddSessionCounter(5,1);
    LoadOverlaySync_020ca630(0xb3,0);
    return;
  case 0xbb:
    ClearSlotMenuSessionStateWordsThunk();
    AddSessionCounter(5,1);
    LoadOverlaySync_020ca630(0xb6,0);
    return;
  case 0xb9:
    ApplySlotMenuThresholdRankBonus(1);
    LoadOverlaySync_020ca630(0xb4,0);
    return;
  case 0xba:
    ApplySlotMenuThresholdRankBonus(2);
    LoadOverlaySync_020ca630(0xb5,0);
    return;
  case 0xbc:
    AddToSelectionCounters_020ca530(1000);
    ClearSlotMenuSessionStateWordsThunk();
    AddSessionCounter(5,1);
    LoadOverlaySync_020ca630(0xb7,0);
    return;
  case 0xbd:
    ApplySlotMenuThresholdRankBonus(4);
    AddToSelectionCounters_020ca530(1000);
    ClearSlotMenuSessionStateWordsThunk();
    AddSessionCounter(5,1);
    AddSessionCounter(0x12,1);
    LoadOverlaySync_020ca630(0xb8,0);
  }
  return;
}
