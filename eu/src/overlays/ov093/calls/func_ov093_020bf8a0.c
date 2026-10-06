#include "nitro/types.h"

extern unsigned char gTrophyReportResourcePaths;
extern unsigned int Msg_OpenContainerAndReadHeader();

void func_ov093_020bf8a0(int resources) {
  void *resource;
  int index;

  index = 0;
  do {
    resource = Msg_OpenContainerAndReadHeader
                       (*(void **)(&gTrophyReportResourcePaths + index * 4),0xe,0);
    *(void **)(resources + index * 4) = resource;
    index = index + 1;
  } while (index < 3);
}
