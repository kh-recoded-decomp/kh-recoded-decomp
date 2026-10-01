#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e0;
extern unsigned int DrawVisibleSceneSlots_02067d48();
extern unsigned int RunFlaggedEventCallbacks_0206daa8();
extern unsigned int _fp_init_020876ac();
extern unsigned int func_02035dd0();
extern unsigned int func_020bd284();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov021_020af508();
extern unsigned int func_ov035_020bae74();
extern unsigned int func_ov035_020bb73c();
extern unsigned int func_ov040_020bdb50();

void func_ov035_020ba75c(void) {
  int work;
  u32 active;
  int blocked;

  work = data_ov035_020bc4e0;
  if ((*(u16 *)(data_ov035_020bc4e0 + 0x24) & 0x80) != 0) {
    func_ov021_020af508(1);
  }
  if ((*(u16 *)(work + 0x22) & 1) != 0) {
    DrawVisibleSceneSlots_02067d48();
  }
  if ((*(u16 *)(work + 0x22) & 4) != 0) {
    func_ov035_020bb73c();
  }
  active = func_ov001_0206dc38();
  if (((0 < (int)active) && (blocked = func_ov035_020bae74(), blocked == 0)) &&
     ((*(u16 *)(work + 0x22) & 8) != 0)) {
    RunFlaggedEventCallbacks_0206daa8();
  }
  if ((*(u16 *)(work + 0x22) & 0x40) != 0) {
    func_02035dd0();
  }
  if ((*(u16 *)(work + 0x22) & 0x10) != 0) {
    _fp_init_020876ac();
  }
  blocked = func_ov035_020bae74();
  if (blocked != 0) {
    func_020bd284();
  }
  if ((*(u16 *)(work + 0x22) & 0x100) != 0) {
    func_ov040_020bdb50();
  }
}
