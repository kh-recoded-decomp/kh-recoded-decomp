extern unsigned int func_ov042_020bd810();

unsigned int ScriptOp_GetFirstSharedValue_020b0c7c(int context)

{
  unsigned int value;
  unsigned char otherValue [4];
  
  func_ov042_020bd810(&value,otherValue);
  *(unsigned short *)(context + 0x2c) = 0x10;
  *(unsigned int *)(context + 0x30) = value;
  return 0;
}
