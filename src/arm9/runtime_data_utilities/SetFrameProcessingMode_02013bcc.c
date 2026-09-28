extern int frame_processing_state[];
extern void *frame_callback_primary;
extern void *frame_callback_secondary;
extern void func_02013d74(int processing_mode);
extern void func_02013c18(void);
extern void func_02013d34(void);

void SetFrameProcessingMode_02013bcc(int processing_mode, int install_callbacks) {
    frame_processing_state[2] = processing_mode;
    func_02013d74(processing_mode);

    if (install_callbacks != 0) {
        frame_callback_primary = func_02013c18;
        frame_callback_secondary = func_02013d34;
    }
}
