extern unsigned int _data_ov021_020b5608;
extern unsigned int func_ov021_020a8810();

unsigned int GetGroupMemberCount_020a8e64(int groupId)

{
  int group;
  unsigned int count;
  
  count = 0;
  if (_data_ov021_020b5608 == 0) {
    return 0;
  }
  group = func_ov021_020a8810(groupId);
  if (group != 0) {
    count = *(unsigned int *)(group + 4);
  }
  return count;
}
