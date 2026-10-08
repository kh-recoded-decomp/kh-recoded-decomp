typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *Actor_Create(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov059_020c7480(void)
{
    SetOverlayObjectFactory(Actor_Create);
}
