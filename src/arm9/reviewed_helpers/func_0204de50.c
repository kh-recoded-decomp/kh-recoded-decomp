#include "nitro/types.h"

extern unsigned int data_0206084c;
extern unsigned int NNS_SndArcStrmStartPrepared_0202029c();

unsigned int func_0204de50(int streamIndex) {
  if (*(unsigned char *)(data_0206084c + streamIndex * 8 + 0xb44ce) == '\x02') {
    NNS_SndArcStrmStartPrepared_0202029c((void *)(data_0206084c + 0xb44c0 + streamIndex * 4));
    return 1;
  }
  return 0;
}
