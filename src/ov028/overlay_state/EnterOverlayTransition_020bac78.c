extern unsigned int _data_ov028_020bb380;
extern unsigned int func_ov001_02066810();
extern unsigned int func_ov001_02087628();

unsigned int EnterOverlayTransition_020bac78(void)

{
  unsigned short flags;
  
  flags = *(unsigned short *)(_data_ov028_020bb380 + 6);
  flags |= 0x20;
  *(unsigned short *)(_data_ov028_020bb380 + 6) = flags;
  if ((flags & 0x10) == 0) {
    func_ov001_02066810();
    func_ov001_02087628(1);
  }
  return 0xf;
}
