extern unsigned int _data_ov025_020b7760;
extern unsigned int func_ov025_020b582c();
extern unsigned int func_ov025_020b5908();
extern unsigned int func_ov027_020ba1d8();
extern unsigned int func_ov027_020ba1e0();

void LoadMenuWidgetResource_020b5954(unsigned int resource)

{
  unsigned int menu;
  unsigned int handle;
  
  menu = _data_ov025_020b7760;
  handle = func_ov027_020ba1d8(resource);
  func_ov025_020b5908(menu,handle);
  func_ov027_020ba1e0(resource,1);
  func_ov025_020b582c(menu);
  return;
}
