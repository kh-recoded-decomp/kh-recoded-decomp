

unsigned int GetMemberByIndex_020adaac(int *container,int index)

{
  if (index >= container[1]) {
    return 0;
  }
  return *(unsigned int *)(*container + index * 4);
}
