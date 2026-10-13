typedef void (*DSProtInitializer)(void);

extern void __sinit_ov104_020d2028(void);
extern void __sinit_ov104_020d25d0(void);
extern void __sinit_ov104_020d2958(void);
extern void __sinit_ov104_020d31fc(void);
extern void __sinit_ov104_020d36b4(void);

/* FS_StartOverlay invokes these entries in order before DSProt is used. */
#pragma define_section dsprotInitializers ".ctor" RW
__declspec(dsprotInitializers) DSProtInitializer gDSProtInitializers[5] = {
    __sinit_ov104_020d2028,
    __sinit_ov104_020d25d0,
    __sinit_ov104_020d2958,
    __sinit_ov104_020d31fc,
    __sinit_ov104_020d36b4,
};
