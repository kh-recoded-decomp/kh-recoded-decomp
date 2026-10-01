extern unsigned int _data_ov023_020b6f64;
extern unsigned int func_0202b554();
extern unsigned int func_ov001_0207b4d8();
extern unsigned int func_ov027_020ba1d8();
extern unsigned int func_ov027_020ba1e0();

void LoadMenuScreenResource_020b5b94(unsigned int resource)

{
  int menu;
  unsigned int handle;
  
  menu = _data_ov023_020b6f64;
  handle = func_ov027_020ba1d8(resource);
  *(unsigned int *)(menu + 0x10) = handle;
  func_0202b554(menu + 0x14,*(unsigned int *)(menu + 0x10),0,0,0xffffffff);
  func_ov027_020ba1e0(resource,0);
  *(unsigned int *)(menu + 0x28) = 1;
  func_ov001_0207b4d8();
  return;
}
