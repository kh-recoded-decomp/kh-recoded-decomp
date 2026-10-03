#include "nitro/types.h"

extern u8 data_ov002_0206c470;

extern void func_ov002_02066ff8(u32 value);
extern void func_ov002_02067170(u32 value);
extern void ImportSlotConfigFlags_0206739c(u32 value);
extern void SetContextConfigByte1ac8_02067444(u32 value);
extern void SetContextConfigFlag1ac8_0206746c(u32 value);
extern void SetContextConfigNibble_02067494(u32 value);
extern void SetClampedPercentValue_020674fc(u32 value);
extern void func_ov002_02067538(u32 value);
extern void func_ov002_02067564(u32 value);
extern void func_ov002_0206762c(u32 value, u32 extra);
extern void func_ov002_02067708(u32 value, u32 extra);
extern void func_ov002_020678cc(u32 value, void *buffer);
extern void func_ov002_020678fc(u32 value, void *buffer);
extern void SetSlotConfigFlag38_020677e4(u32 value, u32 extra);
extern void SetSlotConfigFlag38_02067840(u32 value, u32 extra);
extern void SetSlotConfigFlag38_02067870(u32 value, u32 extra);
extern void func_ov002_0206793c(u32 value, u32 extra, void *buffer);
extern void WriteGlobalPackedFlag_020679dc(int flagIndex, u32 value);
extern void SetContextConfigByte1ba2_02067a0c(u32 value);
extern void SetContextConfigFlag1ad0_02067a5c(u32 value);
extern void func_ov002_020679ac(u32 value, u32 extra);
extern void func_ov002_02067974(u32 value, u32 extra, void *buffer);

extern void LoadStoredPlayerCard_020671f4(void *buffer);
extern u32 GetContextSlotCount_020672f4(void);
extern u32 IsContextSlotFlagSet_02067310(u32 value);
extern void ExportSlotConfigFlags_02067334(u32 value);
extern u32 GetContextConfigByte1ac8_0206740c(void);
extern u32 GetContextConfigFlag1ac8_02067428(void);
extern u32 GetContextConfigNibble1ac8_020674e0(void);
extern u32 func_ov002_02067524(void);
extern u32 GetContextConfigField1acc_02067548(void);
extern u32 func_ov002_020676c4(u32 value);
extern u32 IsTierMaskBitSet_020677a0(u32 value);
extern u32 IsSlotConfigFlagClear_02067814(u32 value);
extern u32 IsContextSlotFlag19Set_020678a0(u32 value);
extern u32 func_ov002_020679fc(int flagIndex);
extern u32 GetContextConfigByte1ba2_02067a2c(void);
extern u32 GetContextConfigFlag1ad0_02067a40(void);

u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer)
{
    if (command & 0x80000000) {
        data_ov002_0206c470 = 1;
        switch (command) {
        case 0x80000001:
            func_ov002_02066ff8(value);
            break;
        case 0x80000002:
            func_ov002_02067170(value);
            break;
        case 0x80000003:
            ImportSlotConfigFlags_0206739c(value);
            break;
        case 0x80000004:
            SetContextConfigByte1ac8_02067444(value);
            break;
        case 0x80000005:
            SetContextConfigFlag1ac8_0206746c(value);
            break;
        case 0x80000006:
            SetContextConfigNibble_02067494(value);
            break;
        case 0x80000007:
            SetClampedPercentValue_020674fc(value);
            break;
        case 0x80000008:
            func_ov002_02067538(value);
            break;
        case 0x80000009:
            func_ov002_02067564(value);
            break;
        case 0x8000000a:
            func_ov002_0206762c(value, extra);
            break;
        case 0x8000000b:
            func_ov002_02067708(value, extra);
            break;
        case 0x8000000c:
            func_ov002_020678cc(value, buffer);
            break;
        case 0x8000000d:
            func_ov002_020678fc(value, buffer);
            break;
        case 0x8000000e:
            SetSlotConfigFlag38_020677e4(value, extra);
            break;
        case 0x8000000f:
            SetSlotConfigFlag38_02067840(value, extra);
            break;
        case 0x80000010:
            SetSlotConfigFlag38_02067870(value, extra);
            break;
        case 0x80000011:
            func_ov002_0206793c(value, extra, buffer);
            break;
        case 0x80000012:
            WriteGlobalPackedFlag_020679dc(0x48, value);
            break;
        case 0x80000013:
            WriteGlobalPackedFlag_020679dc(0x47, value);
            break;
        case 0x80000014:
            WriteGlobalPackedFlag_020679dc(0x4c, value);
            break;
        case 0x80000015:
            WriteGlobalPackedFlag_020679dc(0xb9, value);
            break;
        case 0x80000016:
            SetContextConfigByte1ba2_02067a0c(value);
            break;
        case 0x80000017:
            SetContextConfigFlag1ad0_02067a5c(value);
            break;
        case 0x80000018:
            func_ov002_020679ac(value, extra);
            break;
        case 0x80000019:
            func_ov002_02067974(value, extra, buffer);
            break;
        }
    } else {
        switch (command) {
        case 0:
            LoadStoredPlayerCard_020671f4(buffer);
            break;
        case 1:
            return GetContextSlotCount_020672f4();
        case 2:
            return IsContextSlotFlagSet_02067310(value);
        case 3:
            ExportSlotConfigFlags_02067334(value);
            break;
        case 4:
            return GetContextConfigByte1ac8_0206740c();
        case 5:
            return GetContextConfigFlag1ac8_02067428();
        case 6:
            return GetContextConfigNibble1ac8_020674e0();
        case 7:
            return func_ov002_02067524();
        case 8:
            return GetContextConfigField1acc_02067548();
        case 9:
            return func_ov002_020676c4(value);
        case 10:
            return IsTierMaskBitSet_020677a0(value);
        case 11:
            return IsSlotConfigFlagClear_02067814(value);
        case 12:
            return IsContextSlotFlag19Set_020678a0(value);
        case 13:
            return func_ov002_020679fc(0x48);
        case 14:
            return func_ov002_020679fc(0x47);
        case 15:
            return func_ov002_020679fc(0x4c);
        case 16:
            return func_ov002_020679fc(0xb9);
        case 17:
            return GetContextConfigByte1ba2_02067a2c();
        case 18:
            return GetContextConfigFlag1ad0_02067a40();
        }
    }
    return 0;
}
