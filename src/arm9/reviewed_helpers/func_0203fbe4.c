#include "nitro/types.h"

extern u32 UpdatePenetrationDepth_0203d8b4();
extern u32 VEC_DotProduct_01ff9e6c();

void func_0203fbe4(int extent,void *offset,void *axis,u8 feature,void *result) {
  int distance;

  distance = VEC_DotProduct_01ff9e6c(axis,offset);
  UpdatePenetrationDepth_0203d8b4(extent,distance,axis,feature,result);
}
