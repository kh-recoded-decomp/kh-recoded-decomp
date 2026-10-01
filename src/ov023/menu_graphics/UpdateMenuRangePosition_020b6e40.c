extern unsigned int _data_ov023_020b6f64;
extern unsigned int func_ov023_020b699c();

void UpdateMenuRangePosition_020b6e40(int minimum,int maximum,int value)

{
  unsigned int position;
  
  if (*(int *)(_data_ov023_020b6f64 + 0x34) != 0) {
    position = func_ov023_020b699c(minimum,maximum,value);
    *(unsigned int *)(_data_ov023_020b6f64 + 0x7fa8) = position;
  }
  return;
}
