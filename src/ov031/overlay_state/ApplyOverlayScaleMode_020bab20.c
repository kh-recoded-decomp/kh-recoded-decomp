extern unsigned int _data_ov031_020bc800;
extern unsigned int func_020360a0();
extern unsigned int func_ov001_020668e4();
extern unsigned int func_ov001_02067d80();
extern unsigned int func_ov001_0206d95c();
extern unsigned int func_ov001_0207ecc4();
extern unsigned int func_ov001_02087694();
extern unsigned int func_ov031_020babf8();
extern unsigned int func_ov031_020bb054();

void ApplyOverlayScaleMode_020bab20(int preserveState)

{
  unsigned int scale;
  
  if ((*(unsigned short *)(_data_ov031_020bc800 + 6) & 0x40) != 0) {
    scale = 0x100;
  }
  else {
    scale = 0x1000;
  }
  func_ov031_020babf8();
  func_ov031_020bb054();
  if (preserveState == 0) {
    func_ov001_02067d80(0x1000);
    func_ov001_0207ecc4(0x1000);
  }
  func_ov001_0206d95c(scale);
  if (preserveState == 0) {
    func_ov001_02087694(scale);
    func_ov001_020668e4();
  }
  func_020360a0(0x1000);
  return;
}
