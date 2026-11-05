# Shared session-buffer slots

`src/overlays/ov001/SessionBuffers.h` describes the recovered eight-byte slot
record and its public API. This is a DS memory-layout view, not the complete
type or allocation size of the surrounding context.

| Field | Slot offset | Meaning |
|---|---|---|
| `address` | `0x00` | 32-bit ARM data address returned by the allocator. |
| `size` | `0x04` | Requested payload size, in bytes. |

The table starts at `data_ov001_020a0480 + 0x283c`, where the global word holds
the context's address. Slots have an eight-byte stride. `AllocSessionBuffer`
independently defines the same pointer/size pair and writes those two fields;
the getters read them and the release operation clears them after freeing.
That establishes the record layout without assigning a speculative full type
to the context or inventing a table capacity.

## API and ownership

| Function | Behavior |
|---|---|
| `AllocSessionBuffer(index, size)` | Calls the existing default-heap allocator with `(size, -4)`, stores its returned address and the requested size, and returns the pointer. It does not zero the buffer or free a previous allocation in that slot. |
| `SessionBuffer_GetAddress(index)` | Returns the stored 32-bit address. Formerly `func_ov001_0206468c`, EU `0x0206468c`, 24 bytes. |
| `SessionBuffer_GetSize(index)` | Returns the stored requested byte size. Formerly `func_ov001_020646a4`, EU `0x020646a4`, 20 bytes. |
| `SessionBuffer_Free(index)` | If the address is nonzero, passes that block to `NNSi_FndFreeFromDefaultHeap`, then clears address and size. Formerly `func_ov001_020646b8`, EU `0x020646b8`, 40 bytes. |

All four require an initialized context and a valid slot index. They perform
no null-context or bounds check. A null buffer address is handled by the release
operation, but that does not make a null context valid. If a slot has address
zero and nonzero size, releasing it leaves both fields unchanged; release does
not unconditionally clear the size. Allocation writes the requested size even
if its returned address is zero, so the size getter alone is not a general
allocation-success predicate. The allocator's failure policy and heap behavior
remain the allocator's contract.

The table retains the allocation across its callers. Replacing an occupied
record does not release its previous block; callers remain responsible for that
block's lifetime. Do not assume that allocation is a transactional replacement
or that the payload has been initialized.

## Established callers

`InitResultsScene` uses slot 10 for the results parameter buffer. It allocates
and clears a `ResultsParams` record when the recorded size is zero, and reuses
the stored address on its other path. `CloseResultsSession` calls the release
operation for slot 10 on its corresponding closing path. `CreateBoardScreen`
also reads slot 10. This shows that the slot is shared across scene code; it
does not prove one complete payload type or one universal lifetime for every
possible caller and session mode.

The two getters, release function and these callers now include the same
header. Two overlay-32 wrappers also bind the shared source to this API:
`InitSceneOverlayState` converts the stored DS address to its existing
`SceneContext *` view, and `DestroySceneState` releases slot 10. The inline
pointer adapter expresses that conversion without adding an exported function
or changing the call ABI. These wrappers explicitly include the EU fixed-width
types before the shared source, whose separate legacy header otherwise uses
`long` for 32-bit integers under CodeWarrior. A host port should replace both
views with consistent host types. `CreateBoardScreen` previously declared the address getter as returning
`void *`, while the definition returned `u32`. Its DS call now uses the actual
`u32` interface with an explicit pointer conversion. This changes no ARM
register or instruction, but makes the declaration consistent.

The old release source called an unprototyped free routine without expressing
its block argument. Its matched instructions already left the loaded address
in r0. The current C uses the callee's actual `void (void *)` prototype and
passes the block explicitly. It still reproduces the same instructions and
references. A port no longer has to rely on incidental argument-register
contents when reading this operation.

## Guidance for a host port

Use one pointer-bearing host record and consistent declarations across its
allocator, getters and release function. Resolve or replace the DS address
representation deliberately: casting a 64-bit host pointer to this slot's
`u32` would truncate it. Preserve the observed ownership, initialization and
empty-slot behavior, and establish valid indexes and context lifetime from the
callers before adding a checked host interface.

The context global retains its address-based name. The three slot operations
and this allocator do not establish the meaning and size of all preceding
context fields, so this block does not rename it as a complete session-state
object or manufacture a padded structure ending at the table.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/SessionBuffer_GetAddress.c SessionBuffer_GetAddress --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SessionBuffer_GetSize.c SessionBuffer_GetSize --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SessionBuffer_Free.c SessionBuffer_Free --thumb
python tools/verify_idx.py src/overlays/ov024/calls/CreateBoardScreen.c CreateBoardScreen --thumb
python tools/verify_idx.py src/overlays/ov034/calls/InitResultsScene.c InitResultsScene
python tools/verify_idx.py src/overlays/ov034/calls/CloseResultsSession.c CloseResultsSession
python tools/verify_idx.py src/overlays/ov032/calls/InitSceneOverlayState.c InitSceneOverlayState --thumb
python tools/verify_idx.py src/overlays/ov032/calls/DestroySceneState.c DestroySceneState --thumb
bash tools/gate.sh
```

The three callees match 24, 20 and 40 bytes; their established callers match
832, 1972, 536, 400 and 156 bytes. The full gate must also preserve all module bytes,
including callback references and data placement. Naming adds no C or DATA
reconstruction credit.
