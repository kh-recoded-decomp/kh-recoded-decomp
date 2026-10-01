extern unsigned int func_ov017_020a4ee0();
extern unsigned int func_ov017_020a4efc();

void AppendFieldLinkedEntry_020a4f20(int *head,int entry)

{
  int tail;
  int lastEntry;
  unsigned int firstEntry;
  
  if (*head == 0) {
    *head = entry;
    if ((*(unsigned char *)(entry + 1) & 1) != 0) {
      *(int *)(entry + 4) = entry;
    }
    else {
      *(unsigned int *)(entry + 4) = 0;
    }
    *(unsigned char *)(entry + 1) = *(unsigned char *)(entry + 1) | 2;
    return;
  }
  tail = func_ov017_020a4ee0(*head);
  lastEntry = func_ov017_020a4ee0(entry);
  if (tail != 0) {
    *(unsigned char *)(tail + 1) = *(unsigned char *)(tail + 1) & 0xfd;
  }
  *(unsigned char *)(lastEntry + 1) = *(unsigned char *)(lastEntry + 1) | 2;
  *(int *)(tail + 4) = entry;
  *(unsigned int *)(lastEntry + 4) = 0;
  firstEntry = func_ov017_020a4efc(*head);
  *(unsigned int *)(lastEntry + 4) = firstEntry;
  return;
}
