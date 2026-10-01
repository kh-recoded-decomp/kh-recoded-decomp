extern unsigned int _data_ov021_020b5608;
extern unsigned int func_ov021_020a8810();

int GetGroupMemberData_020a8eec(unsigned int groupId,int index)

{
  int *group;
  
  if (_data_ov021_020b5608 == 0) {
    return 0;
  }
  group = (int *)func_ov021_020a8810(groupId);
  if (group == (int *)0x0) {
    return 0;
  }
  return *group + index * 0x138 + 8;
}
