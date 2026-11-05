typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *Actor_Create(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay059ActorFactory(void)
{
    SetOverlayObjectFactory(Actor_Create);
}
