extern unsigned int func_0202f4b8();

int GetMaximumAlternateFieldValue_020a2788(unsigned int object)

{
  int value;
  unsigned int index;
  int maximum;
  
  maximum = 0;
  index = 0;
  do {
    value = func_0202f4b8(object,index & 0xffff);
    if (value > maximum) {
      maximum = value;
    }
    index = index + 1;
  } while ((int)index < 5);
  return maximum;
}
