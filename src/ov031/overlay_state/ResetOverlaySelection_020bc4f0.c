extern unsigned int _data_ov031_020bc800;
extern unsigned int func_ov001_0207b49c();
extern unsigned int func_ov031_020bc554();

void ResetOverlaySelection_020bc4f0(void)

{
  unsigned int enabledScale;
  
  *(unsigned int *)(_data_ov031_020bc800 + 0x40) = 0xffffffff;
  func_ov031_020bc554();
  if (*(unsigned char *)(_data_ov031_020bc800 + 0x54) == '\x01') {
    enabledScale = 0x1000;
  }
  else {
    enabledScale = 0;
  }
  func_ov001_0207b49c(0,0x1000,enabledScale);
  return;
}
