typedef void code();
extern unsigned int func_ov001_0206db5c();
extern unsigned int func_ov021_020a7fa0();

void DeactivateCurrentMember_020ad8d8(int container)

{
  int owner;
  code *callback;
  
  if (*(int *)(container + 8) != 0) {
    callback = *(code **)(*(int *)(container + 8) + 0x2c);
    if (callback != (code *)0x0) {
      (*callback)(container,*(int *)(container + 8));
    }
    owner = func_ov001_0206db5c(*(unsigned int *)(container + 0x14));
    func_ov021_020a7fa0(owner + 0xb2c,0xffffffff);
    *(unsigned int *)(container + 8) = 0;
  }
  return;
}
