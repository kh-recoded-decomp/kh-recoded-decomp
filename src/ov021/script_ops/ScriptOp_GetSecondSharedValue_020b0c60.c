extern unsigned int func_ov042_020bd810();

unsigned int ScriptOp_GetSecondSharedValue_020b0c60(int context)

{
  unsigned char otherValue [4];
  unsigned int value;
  
  func_ov042_020bd810(otherValue,&value);
  *(unsigned short *)(context + 0x2c) = 0x10;
  *(unsigned int *)(context + 0x30) = value;
  return 0;
}
