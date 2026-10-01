extern unsigned int _data_ov021_020b5608;
extern unsigned int func_ov021_020a8810();

unsigned int IsGroupMemberActive_020a8d1c(unsigned int groupId,int index)

{
  int *group;
  
  if (_data_ov021_020b5608 == 0) {
    return 0;
  }
  group = (int *)func_ov021_020a8810(groupId);
  if (group == (int *)0x0) {
    return 0;
  }
  if (*(char *)(*group + index * 0x138) == '\x01') {
    return 1;
  }
  return 0;
}
