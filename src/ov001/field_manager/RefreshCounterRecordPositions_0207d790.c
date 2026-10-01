#include "nitro/types.h"

extern u32 data_ov001_0209dfd8;
extern u32 data_ov001_0209dfe8;
extern u32 func_ov001_020711b0();
extern u32 func_ov027_020b8184();
extern u32 func_ov027_020b81e0();
extern u32 func_ov027_020b8210();

void RefreshCounterRecordPositions_0207d790(int counter)

{
  u32 container;
  u32 record;
  
  container = func_ov001_020711b0();
  record = func_ov027_020b8184
                    (container,*(u32 *)((u8 *)&data_ov001_0209dfe8 +
                                    (u32)*(u16 *)(counter + *(int *)(counter + 0x2c) * 2 + 0x20)
                                    * 4) & 0xffff);
  func_ov027_020b81e0(container,record,0xf);
  func_ov027_020b8210(container,record);
  record = func_ov027_020b8184
                    (container,*(u32 *)((u8 *)&data_ov001_0209dfd8 +
                                    (u32)*(u16 *)
                                           (counter + (*(u32 *)(counter + 0x2c) ^ 1) * 2 + 0x20) *
                                    4) & 0xffff);
  func_ov027_020b81e0(container,record,0x13);
  func_ov027_020b8210(container,record);
  return;
}
