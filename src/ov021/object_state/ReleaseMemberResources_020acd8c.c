typedef void code();
extern unsigned int func_0202a1c4();

void ReleaseMemberResources_020acd8c(int member,int context)

{
  if (*(code **)(member + 0x20) != (code *)0x0) {
    (**(code **)(member + 0x20))(member,context);
  }
  if (0 < *(int *)(member + 0x14)) {
    func_0202a1c4(*(unsigned int *)(member + 0x10));
  }
  if (*(int *)(member + 0x1c) != 0) {
    func_0202a1c4(*(unsigned int *)(member + 0x18));
  }
  return;
}
