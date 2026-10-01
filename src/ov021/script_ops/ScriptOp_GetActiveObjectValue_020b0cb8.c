extern int contextData_020b56a4[];
#define activeObject_020b56ac contextData_020b56a4[2]
extern unsigned int func_ov001_02091818();

unsigned int ScriptOp_GetActiveObjectValue_020b0cb8(int context)

{
  unsigned int value;
  
  if (activeObject_020b56ac == 0) {
    return 0;
  }
  *(unsigned short *)(context + 0x2c) = 0x10;
  value = func_ov001_02091818(activeObject_020b56ac);
  *(unsigned int *)(context + 0x30) = value;
  return 0;
}
