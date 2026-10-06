typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *func_ov059_020c7a68(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov059_020c7480(void)
{
    SetOverlayObjectFactory(func_ov059_020c7a68);
}
