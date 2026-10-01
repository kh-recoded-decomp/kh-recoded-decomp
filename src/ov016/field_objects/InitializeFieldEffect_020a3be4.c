extern unsigned int func_0204da8c();
extern unsigned int func_ov016_020a296c();
extern unsigned int func_ov016_020a2b38();
extern unsigned int func_ov016_020a2c0c();

void InitializeFieldEffect_020a3be4(int object,unsigned int selection)

{
  unsigned int effect;
  
  *(unsigned int *)(object + 0xd8) = *(unsigned int *)(object + 0xd8) & 0xffffff00 | selection & 0xff;
  *(unsigned int *)(object + 0xcc) = 0;
  effect = func_ov016_020a2b38(object,0x2400,0);
  *(unsigned int *)(object + 0xd0) = effect;
  func_ov016_020a2c0c(object);
  func_ov016_020a296c(object,selection != 0xff);
  *(unsigned char *)(object + 0xbe) = *(unsigned char *)(object + 0xbe) & ~0xf0 | 0x40;
  func_0204da8c(0,0x3d,object + 0x38,0);
  return;
}
