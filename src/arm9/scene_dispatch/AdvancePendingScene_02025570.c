/* Releases a completed scene object, loads a pending scene overlay, creates its object, and clears the pending request.
 * The first BK9E global read uses offset zero and the unload call preserves the overlay ID in r1; resolved calls include overlay load/unload and object creation. Scene identities remain unknown.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_0202099c.c. */


typedef struct SceneEntry {
    int   overlayId;   
    void *classDesc;   
} SceneEntry;

typedef struct SceneCtl {
    void       *obj;      
    SceneEntry *entry;    
    int         curId;    
    int         pendId;   
    int         pendArg;  
} SceneCtl;

extern int  data_0205fdec;           
extern char data_0205fdec_alias[];         
extern SceneEntry data_02055da0[];   
extern void *data_0206039c;

extern int  func_0202a720(void *obj);
extern void func_02029f98(int, int);
extern void func_020253f8(void);
extern void func_0202a0f0(void *);
extern void func_02029f78(int module, int overlayId);
extern void *func_0202a448(void *classDesc, int arg);   
extern void func_0202a5a4(void *obj, int);

int AdvancePendingScene_02025570(void) {
    SceneCtl *s = (SceneCtl *)data_0205fdec_alias;

    if (*(void **)((char *)&data_0205fdec) != 0) {
        if (func_0202a720(s->obj) != 0) {
            if (s->entry->overlayId != -1) {
                func_02029f98(0, s->entry->overlayId);
            }
            func_020253f8();
            func_0202a0f0(data_0206039c);
            s->obj = 0;
            s->curId = 0;
        }
    }

    if (s->obj == 0) {
        int id = s->pendId;
        if (id != 0) {
            SceneEntry *ent = &data_02055da0[id];
            int ov = ent->overlayId;
            if (ov != -1) {
                func_02029f78(0, ov);
            }
            {
                void *obj = func_0202a448(ent->classDesc, s->pendArg);
                s->obj = obj;
                s->entry = ent;
                func_0202a5a4(obj, 1);
            }
            s->curId = s->pendId;
            s->pendId = 0;
            s->pendArg = 0;
        }
    }
    return 1;
}
