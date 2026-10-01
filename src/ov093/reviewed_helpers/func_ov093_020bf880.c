#include "nitro/types.h"

extern unsigned char data_ov093_020c3e80;
extern unsigned int Msg_OpenContainerAndReadHeader_0202cc6c();

void func_ov093_020bf880(int resources) {
  void *resource;
  int index;

  index = 0;
  do {
    resource = Msg_OpenContainerAndReadHeader_0202cc6c
                       (*(void **)(&data_ov093_020c3e80 + index * 4),0xe,0);
    *(void **)(resources + index * 4) = resource;
    index = index + 1;
  } while (index < 3);
}
