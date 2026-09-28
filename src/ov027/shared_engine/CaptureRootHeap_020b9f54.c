extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_020ba3c0;
extern void Ov002_MsgQueue_GetHeap(void);

void (*CaptureRootHeap_020b9f54(void))(void)
{
    data_020ba3c0 = NNSi_FndGetCurrentRootHeap();
    return Ov002_MsgQueue_GetHeap;
}
