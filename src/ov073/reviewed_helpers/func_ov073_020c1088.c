#include "nitro/types.h"

extern unsigned int PlaySoundEffect_0204d924();
extern unsigned int func_020be0c4();
extern unsigned int func_ov039_020bca00();

unsigned int func_ov073_020c1088(int work) {
  int input;
  int result;

  if (*(short *)(work + 0x10f4) <= 1) {
    result = -1;
  }
  else {
    result = func_020be0c4(work + 0x10f4,*(unsigned int *)(work + 0x10e0));
    if ((*(short *)(work + 0x10) != *(short *)(work + 0x10f6)) &&
       (input = func_ov039_020bca00(), (*(u16 *)(input + 8) & 3) == 1)) {
      result = 2;
    }
    *(short *)(work + 0x10) = *(short *)(work + 0x10f6);
  }
  if (result != 1) {
    if (result != 2) goto code_r0x020c10de;
    PlaySoundEffect_0204d924(0,0);
  }
  *(u8 *)(work + 1) = 1;
code_r0x020c10de:
  result = func_ov039_020bca00();
  if ((*(u16 *)(result + 10) & 0xf0) != 0) {
    *(u8 *)(work + 1) = 1;
  }
  return 0;
}
