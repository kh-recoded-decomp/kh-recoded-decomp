extern unsigned int func_ov043_020bca1c();

unsigned int IsOffsetBeyondActiveRecord_020bc594(int firstOffset,int secondOffset)

{
  int record;
  
  record = func_ov043_020bca1c();
  if (firstOffset - secondOffset > *(int *)(record + 8)) {
    return 1;
  }
  return 0;
}
