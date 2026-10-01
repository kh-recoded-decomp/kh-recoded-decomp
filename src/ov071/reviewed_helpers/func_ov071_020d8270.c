#include "nitro/types.h"

extern u32 SetManagerEnabled_0206e160();
extern u32 StopAndClearSoundEmitter_020a8e14();
extern u32 func_ov001_020734f8();

void func_ov071_020d8270(u32 event,int actor) {
  int soundSlot;

  soundSlot = (int)(char)*(u32 *)(actor + 0x80);
  if (soundSlot != -1) {
    StopAndClearSoundEmitter_020a8e14((int)*(short *)(actor + 0x40),soundSlot);
    *(u32 *)(actor + 0x80) = *(u32 *)(actor + 0x80) & 0xffffff00 | 0xff;
  }
  soundSlot = (*(int *)(actor + 0x80) << 0x10) >> 0x18;
  if (soundSlot != -1) {
    StopAndClearSoundEmitter_020a8e14((int)*(short *)(actor + 0x42),soundSlot);
    *(u32 *)(actor + 0x80) = *(u32 *)(actor + 0x80) & 0xffff00ff | 0xff00;
  }
  soundSlot = (*(int *)(actor + 0x80) << 8) >> 0x18;
  if (soundSlot != -1) {
    StopAndClearSoundEmitter_020a8e14((int)*(short *)(actor + 0x42),soundSlot);
    *(u32 *)(actor + 0x80) = *(u32 *)(actor + 0x80) & 0xff00ffff | 0xff0000;
  }
  soundSlot = *(int *)(actor + 0x80) >> 0x18;
  if (soundSlot != -1) {
    StopAndClearSoundEmitter_020a8e14((int)*(short *)(actor + 0x46),soundSlot);
    *(u32 *)(actor + 0x80) = *(u32 *)(actor + 0x80) & 0xffffff | 0xff000000;
  }
  func_ov001_020734f8();
  SetManagerEnabled_0206e160(0);
}
