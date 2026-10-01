extern unsigned int _data_ov031_020bc800;
extern unsigned int func_ov043_020bca1c();

int GetNegatedCombinedOffset_020bc68c(int offset)

{
  int context;
  int record;
  
  context = _data_ov031_020bc800;
  record = func_ov043_020bca1c();
  { int value = *(int *)(*(int *)(context + 0x50) + *(int *)(context + 0x44) * 0x3c);
    value += *(int *)(record + 8);
    return -(offset + value); }
}
