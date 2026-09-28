extern void TP_RequestAutoSamplingStopAsync_0200fe84(void);
extern void TP_WaitBusy_0201018c(int channel);
extern void TP_CheckError_0201019c(int channel);

void StopTouchPanelSampling_0206241c(void)
{
    TP_RequestAutoSamplingStopAsync_0200fe84();
    TP_WaitBusy_0201018c(4);
    TP_CheckError_0201019c(4);
}
