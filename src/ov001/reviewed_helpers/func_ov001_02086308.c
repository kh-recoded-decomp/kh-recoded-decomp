#include "nitro/types.h"

extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int func_01ff8740();
extern unsigned int func_ov001_0208635c();

unsigned int * func_ov001_02086308(unsigned int owner,u8 kind) {
  unsigned int *request;
  void *work;

  request = (unsigned int *)func_ov001_0208635c();
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
  work = NNSi_FndAllocFromDefaultHeap_0202a178(0x1d0);
  request[2] = work;
  func_01ff8740(0,work,0x1d0);
  return request;
}
