#include "nitro/types.h"

extern unsigned int gOv031SceneWorkStorage;
extern unsigned int RemoveGroupObjectsFromTree();
extern unsigned int FlagKind6Objects();
extern unsigned int ReleaseActiveRecordItems();

void ReleaseCurrentSceneRecord(void) {
  int recordOffset;
  int records;

  records = *(int *)(gOv031SceneWorkStorage + 0x50);
  recordOffset = *(int *)(gOv031SceneWorkStorage + 0x44) * 0x3c;
  if (((*(unsigned char *)(records + recordOffset + 0x38) != '\0') || (*(unsigned char *)(records + recordOffset + 0x39) != '\0')) ||
     (*(unsigned char *)(records + recordOffset + 0x3a) != '\0')) {
    *(unsigned char *)(gOv031SceneWorkStorage + 0x58) = *(unsigned char *)(gOv031SceneWorkStorage + 0x58) + '\x01';
  }
  RemoveGroupObjectsFromTree();
  FlagKind6Objects();
  ReleaseActiveRecordItems();
  *(unsigned int *)(gOv031SceneWorkStorage + 0x44) = 0xffffffff;
}
