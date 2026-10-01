#include "nitro/types.h"

#define false 0
#define true 1


int ScaleMatrixInput_020c7cdc(int value,int useHalfScale)

{
  if (useHalfScale != 0) {
    return value / 2;
  }
  return value / 8;
}
