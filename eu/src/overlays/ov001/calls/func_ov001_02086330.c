#include "nitro/types.h"

extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int MIi_CpuClearFast();
extern unsigned int func_ov001_02086384();

unsigned int * func_ov001_02086330(unsigned int owner,u8 kind) {
  unsigned int *request;
  void *work;

  request = (unsigned int *)func_ov001_02086384();
  if (*(unsigned short *)(request + 0xc) != 0) {
    return (unsigned int *)0x0;
  }
  *request = 0;
  *(u16 *)(request + 0xc) = 1;
  request[1] = owner;
  *(u8 *)((int)request + 0x33) = kind;
  *(u16 *)(request + 0x11) = 0xffff;
  *(u8 *)((int)request + 0x46) = 0;
  request[3] = 0;
  work = NNSi_FndAllocFromDefaultHeap(0x1d0);
  request[2] = work;
  MIi_CpuClearFast(0,work,0x1d0);
  return request;
}
