#include "nitro/types.h"

typedef void PanelCallback(void *context);
extern u32 _data_ov015_0207e964;

void InvokePanelCallback_02073598(void *context)

{
  if (*(PanelCallback **)(_data_ov015_0207e964 + 0x90) == (PanelCallback *)0x0) {
    return;
  }
  (**(PanelCallback **)(_data_ov015_0207e964 + 0x90))(context);
  return;
}
