#include "nitro/types.h"

extern unsigned int G2_GetBG2ScrPtr_02006e88();
extern unsigned int G2_GetBG3ScrPtr_02006f80();
extern unsigned int func_01ff8740();
extern unsigned int func_020014f0();
extern unsigned int func_0200153c();
extern unsigned int func_02001574();
extern unsigned int func_0202a1c4();
extern unsigned int func_ov036_020c27a0();
extern unsigned int func_ov036_020c27cc();

void func_ov036_020bee40(int *window) {
  int active;
  unsigned int screen;

  if (window[0x1c] != 0) {
    func_0202a1c4(window[0x1c]);
    window[0x1c] = 0;
    if (*window == 0 || *window == 4) {
      *(unsigned int *)window[0x43] = 0;
    }
  }
  active = func_ov036_020c27a0(window,0);
  if (active != 0) {
    func_02001574(window + 0xf,0);
    func_0200153c(window + 0xf);
    func_020014f0(window + 0xf);
    func_ov036_020c27cc(window,0);
  }
  if (window[0xb] == 2) {
    screen = G2_GetBG2ScrPtr_02006e88();
    func_01ff8740(0,screen,0x800);
    return;
  }
  screen = G2_GetBG3ScrPtr_02006f80();
  func_01ff8740(0,screen,0x800);
}
