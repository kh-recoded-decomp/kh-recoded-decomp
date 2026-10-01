#include "nitro/types.h"

extern u32 UpdateSignedPenetrationDepth_0203d854();
extern u32 VEC_DotProduct_01ff9e6c();

void func_0203fba4(int extent,void *offset,void *axis,u8 feature,void *result) {
  int distance;

  distance = VEC_DotProduct_01ff9e6c(axis,offset);
  UpdateSignedPenetrationDepth_0203d854(extent,distance,axis,feature,result);
}
