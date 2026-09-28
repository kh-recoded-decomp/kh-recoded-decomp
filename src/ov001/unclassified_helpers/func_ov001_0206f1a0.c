#include "nitro/types.h"

extern u32 data_ov001_0209ed0c;
extern u32 data_ov001_0209ed24;
extern u32 data_ov001_0209ed3c;
extern u32 data_ov001_0209ed54;
extern void func_02001458(u32 context, u32 *table);

void func_ov001_0206f1a0(u32 context)
{
    func_02001458(context + 0x9c, &data_ov001_0209ed0c);
    func_02001458(context + 0x78, &data_ov001_0209ed24);
    func_02001458(context + 0x84, &data_ov001_0209ed3c);
    func_02001458(context + 0x90, &data_ov001_0209ed54);
}
