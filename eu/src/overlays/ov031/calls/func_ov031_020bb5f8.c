#include "nitro/types.h"

extern unsigned int data_ov031_020bc820;
extern unsigned int RemoveGroupObjectsFromTree();
extern unsigned int FlagKind6Objects();
extern unsigned int ReleaseActiveRecordItems();

void func_ov031_020bb5f8(void) {
  int recordOffset;
  int records;

  records = *(int *)(data_ov031_020bc820 + 0x50);
  recordOffset = *(int *)(data_ov031_020bc820 + 0x44) * 0x3c;
  if (((*(unsigned char *)(records + recordOffset + 0x38) != '\0') || (*(unsigned char *)(records + recordOffset + 0x39) != '\0')) ||
     (*(unsigned char *)(records + recordOffset + 0x3a) != '\0')) {
    *(unsigned char *)(data_ov031_020bc820 + 0x58) = *(unsigned char *)(data_ov031_020bc820 + 0x58) + '\x01';
  }
  RemoveGroupObjectsFromTree();
  FlagKind6Objects();
  ReleaseActiveRecordItems();
  *(unsigned int *)(data_ov031_020bc820 + 0x44) = 0xffffffff;
}
