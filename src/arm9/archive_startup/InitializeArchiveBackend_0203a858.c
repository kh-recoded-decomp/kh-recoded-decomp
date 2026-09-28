extern void func_02039d54(void);
extern void func_02039d7c(void);
extern void func_01ffe280(void);
extern void func_01ffe394(void);
extern void func_01ffe3d8(void);
extern void func_01ffe8a0(void);
extern void func_01ffe934(void);
extern void func_02039da4(void);
extern void func_02039fec(void);
extern void func_01ffec28(void);
extern void func_0203a28c(void);
extern void func_01fff374(void);
extern void func_0203a2f4(void);
extern void func_0203a574(void);
extern void srand_0x02016284(unsigned seed);
extern void *archive_backend_callbacks[];

void InitializeArchiveBackend_0203a858(void) {
    archive_backend_callbacks[0] = (void *)&func_02039d54;
    archive_backend_callbacks[1] = (void *)&func_02039d7c;
    archive_backend_callbacks[2] = (void *)&func_01ffe280;
    archive_backend_callbacks[3] = (void *)&func_01ffe394;
    archive_backend_callbacks[4] = (void *)&func_01ffe3d8;
    archive_backend_callbacks[5] = (void *)&func_01ffe8a0;
    archive_backend_callbacks[6] = (void *)&func_01ffe934;
    archive_backend_callbacks[7] = (void *)&func_02039da4;
    archive_backend_callbacks[8] = (void *)&func_02039fec;
    archive_backend_callbacks[9] = (void *)&func_01ffec28;
    archive_backend_callbacks[10] = (void *)&func_0203a28c;
    archive_backend_callbacks[11] = (void *)&func_01fff374;
    archive_backend_callbacks[12] = (void *)&func_0203a2f4;
    archive_backend_callbacks[13] = (void *)&func_0203a574;
    srand_0x02016284(1);
}
