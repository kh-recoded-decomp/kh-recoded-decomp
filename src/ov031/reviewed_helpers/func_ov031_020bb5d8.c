#include "nitro/types.h"

extern unsigned int data_ov031_020bc800;
extern unsigned int func_ov031_020bbde4();
extern unsigned int func_ov031_020bbe48();
extern unsigned int func_ov031_020bbe6c();

void func_ov031_020bb5d8(void) {
  int recordOffset;
  int records;

  records = *(int *)(data_ov031_020bc800 + 0x50);
  recordOffset = *(int *)(data_ov031_020bc800 + 0x44) * 0x3c;
  if (((*(unsigned char *)(records + recordOffset + 0x38) != '\0') || (*(unsigned char *)(records + recordOffset + 0x39) != '\0')) ||
     (*(unsigned char *)(records + recordOffset + 0x3a) != '\0')) {
    *(unsigned char *)(data_ov031_020bc800 + 0x58) = *(unsigned char *)(data_ov031_020bc800 + 0x58) + '\x01';
  }
  func_ov031_020bbde4();
  func_ov031_020bbe48();
  func_ov031_020bbe6c();
  *(unsigned int *)(data_ov031_020bc800 + 0x44) = 0xffffffff;
}
