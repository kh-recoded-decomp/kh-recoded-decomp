#include "nitro/types.h"

extern char data_ov099_020c286c[];
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern int *func_0202c478(u32 fileId, u32 param2);

void LoadViewerModelTable_020c1a98(u32 *viewer) {
  int index;
  u32 header;
  int *table;

  header = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov099_020c286c, 0xe, 0);
  viewer[0x29] = header;
  table = func_0202c478(((header + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0xe);
  viewer[0] = (u32)table;
  for (index = 0; index < 0x28; index++) {
    viewer[index + 1] = (u32)table;
    table = table + *table + 1;
  }
}
