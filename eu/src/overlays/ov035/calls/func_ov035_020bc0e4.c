extern unsigned int *data_ov035_020bc508[];
#define puRam020c006c data_ov035_020bc508[1]
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void func_ov035_020bc0e4(void)

{
  unsigned int *buffers;

  buffers = puRam020c006c;
  NNSi_FndFreeFromDefaultHeap(*puRam020c006c);
  NNSi_FndFreeFromDefaultHeap(buffers[1]);
  NNSi_FndFreeFromDefaultHeap(buffers[3]);
  NNSi_FndFreeFromDefaultHeap(buffers[2]);
  puRam020c006c = (unsigned int *)0x0;
  return;
}
