extern unsigned int *gAreaSceneGaugeGlobalsStorage[];
#define puRam020c006c gAreaSceneGaugeGlobalsStorage[1]
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void ReleaseAreaGaugeBuffers(void)

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
