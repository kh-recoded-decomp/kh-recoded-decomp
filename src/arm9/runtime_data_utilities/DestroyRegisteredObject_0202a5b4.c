extern int  func_0202a134(int arena);
extern void func_0202a3a8(int node);
extern void NNSi_FndFreeFromDefaultHeap(void *unknown_argument_p);
extern void func_0202a240(void *obj, void *heap);
extern int  object_registry[];
extern int  default_heap[];

int DestroyRegisteredObject_0202a5b4(int *object)
{
    int saved_value;
    void (*destructor)(void);
    int arena_state;

    arena_state = func_0202a134(object[7]);
    saved_value = object_registry[1];
    object_registry[1] = (int)object;
    destructor = (void (*)(void))object[6];
    if (destructor != 0) {
        destructor();
    }
    *object = 0;
    object_registry[1] = saved_value;
    func_0202a3a8((int)object);
    saved_value = object[3];
    if (object[8] != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)object[8]);
    }
    func_0202a240(object, (void *)default_heap[0]);
    func_0202a134(arena_state);
    return saved_value;
}
