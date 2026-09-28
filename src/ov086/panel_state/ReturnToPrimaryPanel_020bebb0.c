#include "nitro/types.h"

extern u8 *func_ov039_020bc1bc(void);
extern void func_ov027_020b9874(u8 *panel, BOOL enable);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ReturnToPrimaryPanel_020bebb0(void)
{
    func_ov027_020b9874(func_ov039_020bc1bc(), TRUE);
    SetPrimaryElementEnabled_020bc054(TRUE);
    SetSecondaryElementEnabled_020bc084(FALSE);
    PlaySoundEffect_0204d924(0, 3);
}
