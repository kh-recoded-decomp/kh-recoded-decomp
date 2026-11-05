# Field-session handlers and saved placement (EU)

These fifteen functions install overlay-specific callbacks, expose a small set of session fields and transfer a saved placement through packed save bits. Their names describe established operations; the overlay number in an installer identifies its loaded code bank, not a recovered gameplay mode name.

Offsets refer to the 32-bit DS session reached through `data_ov001_020a0480`. The structures used by different source files are partial views. They do not establish a complete host `Session` layout or the allocation size of unrelated fields.

## Overlay-handler installers

Each installer has the logical interface `void(void)`: it obtains the current session and passes `session + 0x280c` to the selected overlay initializer. It neither allocates the session nor owns the callback table storage.

| Installer | EU ov001 entry | Session state selecting it | Actual target bank and entry |
| --- | --- | ---: | --- |
| `InstallSessionOv028Handlers` | `02062ac0`, Thumb | `0` | ov028 `InstallSceneHandlers`, ARM `020bb220` |
| `InstallSessionOv030Handlers` | `02062ad8`, Thumb | `4` | ov030 `InstallSceneHandlers_020bb288`, Thumb `020bb288` |
| `InstallSessionOv031Handlers` | `02062af0`, Thumb | `7` | ov031 `InstallMovieSceneHandlers`, Thumb `020bbf9c` |
| `InstallSessionOv035Handlers` | `02062b84`, Thumb | `6` | ov035 `InitMovieSourceOps`, Thumb `020badb4` |
| `InstallSessionOv032Handlers` | `02062bdc`, Thumb | `10` | ov032 `InstallMovieCallbacks`, Thumb `020bb7bc` |
| `InstallSessionOv029Handlers` | `02062bf4`, Thumb | `3` | ov029 `InstallOv029SceneHandlers`, ARM `020baafc` |
| `InstallSessionOv036Handlers` | `02062c0c`, Thumb | `8` | ov036 `InitPanelCallbackTable`, ARM `020bc4c8` |
| `InstallSessionOv038Handlers` | `02062c4c`, Thumb | `12` | ov038 `InitOv038HandlerTable`, ARM `020ba718` |

`SetSessionState` reads `gSessionStateOverlayIds[newState]`, loads that overlay and then selects the corresponding installer. An installer alone does not load or retain its target overlay. The caller must satisfy the code-bank and session-lifetime preconditions.

The native sources commonly declare a target as a byte array or scalar symbol and cast its address to a function pointer. This is an erased representation of a code entry, not evidence that the target is a data buffer or accepts a particular host structure. The actual initializer takes the callback-table address and writes function pointers into it. Recover callback signatures individually before creating a host interface.

### The overlay-36 identity

The ov001 entry `02062c0c` historically referred to `data_ov035_020bc4c8`. That is a real DATA object in overlay 35, beginning with the format `%s%02d` and `area` strings and referenced by `LoadFadeModel`.

The caller is selected for session state `8`, whose overlay table entry is `36`. In overlay 36, `020bc4c8` is the ARM function `InitPanelCallbackTable`, with a native extent of `0x74` bytes and stores that install nine callbacks. The loaded bank and actual instruction body establish this identity. The equal numeric RAM address does not make DATA35 the function.

Keep the ov035 data object and its users separate. The native entry binding and the eventual host callback type are distinct issues: an address cast can preserve the original calling boundary without claiming that the old array declaration is the logical API. A typed rewrite must respect the actual ARM/Thumb entry and callback contract.

## Callback storage and consumers

The table begins at session `+0x280c` and spans at least twelve 32-bit slots, through `+0x2838`: **48 bytes**. An old `overlayWork[0x10]` declaration is a placeholder prefix. It is not a safe allocation bound.

| Slot | Session offset | Contract established by the shared consumer |
| ---: | --- | --- |
| `0` | `+0x280c` | `SetSessionState` calls `init(params)` when the machine handle is `-1` and stores its return word as the handle. |
| `1` | `+0x2810` | `LeaveFieldMenu` calls optional `canLeave(void)`; FALSE returns `-1` before leaving. |
| `2` | `+0x2814` | `LeaveFieldMenu` calls optional `onLeave(void)` after the predicate permits exit. |
| `3` | `+0x2818` | Finish/close callback taking an integer. `SelectNextSessionState`, `StepSessionScriptOrAbort` and `020648c8` pass the sign-extended byte at `+0x28a4`, or explicit zero on specific paths. |
| `4` | `+0x281c` | No-argument poll callback. Nonzero permits progress in its consumers; missing-callback rules differ as described below. |
| `5` | `+0x2820` | No-argument shutdown callback. `ShutdownSessionOverlays` calls it without a NULL check when the machine handle exists. |
| `6` | `+0x2824` | Optional `update(params)` called by `SetSessionState` when a handle already exists. |
| `7` | `+0x2828` | Optional readiness predicate used by `02062c64` before raising a script run flag or entering the linked-session path. FALSE blocks that gate. |
| `8` | `+0x282c` | Optional callback invoked by `InvokeSessionCallback` with the forwarded argument. Its operation is overlay-specific. |
| `9` | `+0x2830` | Not written by the reviewed installers; no operation is assigned. |
| `10` | `+0x2834` | Raw no-argument check result used by `02064490` and `RunSessionCheckCallback`. Preserve raw masks and each wrapper's default. |
| `11` | `+0x2838` | Optional no-argument callback invoked by `02064de8` through script command `02065f2c`. Its precise effect depends on the installed overlay. |

The parameter record passed to slots 0 and 6 is eight bytes at session `+0x28a4`: a mode byte, signed context-mode byte and three 16-bit values. `SetSessionState` fills those fields before initialization/update. Slot 3 instead receives the sign-extended first byte, not a pointer to that record.

The callback array is heterogeneous. An array of `void (*)(void)` reproduces DS pointer words but is not a valid universal host calling interface. Slot 6 is the state-machine parameter update; slot 8 is the forwarded-argument callback. Private labels that call both “update” do not establish identical signatures.

### Missing callbacks and teardown

The null cases have different meanings:

- `WaitSessionPollCallback` advances to state `11` when slot 4 is absent, and waits when a present callback returns FALSE.
- `WaitSessionPollAndClearFlags` waits when slot 4 is absent. On a nonzero result, it clears session flag bits 6 and 7 and advances to state `6`.
- `02062c64` permits an absent slot 7, but additionally requires `!IsEntryFlag2Active(0)`. The callback alone does not establish overall readiness.
- `02064490` returns slot 10's word unchanged, or `1` when absent. `RunSessionCheckCallback` returns TRUE only when a present callback returns zero; it returns FALSE when absent. These are distinct operations.

When the machine handle is not `-1`, `ShutdownSessionOverlays` invokes slot 5, unloads the target overlay when needed, clears the complete 48-byte callback block and sets the handle to `-1`. The clear is conditional on the handle; do not assume an installer individually zeros every unwritten slot. Some initializers install only a subset, and slots 10/11 are not written by every initializer.

The session owns the callback storage. The installed pointers refer to code in an overlay whose lifetime is managed by the surrounding state machine. A port must not retain a pointer after unloading the code it identifies. This does not imply that every callback itself destroys tasks, clears global handles or releases the outer session.

## Session queries

| Function | EU ov001 identity | Logical contract |
| --- | --- | --- |
| `HasSessionContext` | `02063a24`, Thumb | Returns whether the session global pointer is nonzero. |
| `GetSessionResourceArchive` | `020636e4`, Thumb | Returns the borrowed word at session `+0x272c`, used as the shared-resource archive base/handle. |
| `GetFieldSessionState` | `02063a38`, Thumb | Returns the sign-extended byte at session `+0x2808`. |
| `GetSessionFlagsMask20` | `02063838`, Thumb | Returns the raw mask from session word `+0x20 & 0x20`. |

Pointer presence is not a full initialization or task-liveness test. The other getters have no session NULL guard. `GetFieldSessionState` corresponds to the state byte in the machine at session `+0x2800`, and preserves negative sentinels.

`LoadLevelTableFile`, `LoadCameraParams`, `LoadSceneData` and `LoadOffsetTableFile` pass the archive word to shared-name lookup or encoded archive-key construction. Calling the getter does not load an archive, validate a resource name or transfer ownership. A host interface should preserve the archive abstraction instead of truncating a host pointer into a DS-sized word.

The mask getter returns `0` or `0x20`, not Boolean `1`. `StartSessionScene` sets this mask after starting a scene, and the reactivation path at `0206375c` clears it. A narrower gameplay meaning is not assigned. This word at `+0x20` is distinct from the frequently used session flag word at `+0x214`.

## Packed saved placement

| Function | EU ov001 identity | Logical contract |
| --- | --- | --- |
| `StorePackedSessionPlacement` | `020645f4`, Thumb | Stores three input 32-bit words and the low 16 bits of the angle argument. |
| `LoadPackedSessionPlacement` | `02064628`, Thumb | Reads the same three words into caller storage and writes a 16-bit angle. |

The save fields are addressed in bits:

| Input/output | First packed bit | Width |
| --- | --- | ---: |
| Vector word 0 | `0x3537` | `32` |
| Vector word 1 | `0x3557` | `32` |
| Vector word 2 | `0x3577` | `32` |
| Angle | `0x3597` | `16` |

The position/facing interpretation comes from the actual dataflow. `02064884` supplies the managed leader's position and angle. `RestoreSavedPlacement` reads into `savedPositions[0]` and `savedAngles[0]`, applies them to spawn placement and derives follower offsets. `StartFieldSession` also uses the saved placement on the stage-900 path.

Both helpers now expose the vector/angle inputs through `SessionPlacement.h` and use caller-provided storage; they allocate and free nothing. The reader requires writable storage for three words and one halfword. The writer's native extra argument is a word, but only its low 16 bits are represented in the packed field. Remaining shared callers still contain native integer declarations that transport addresses; they do not justify a 32-bit host-pointer API. The two defining helpers now take actual `VecFx32` pointers, while the angle writer retains a word input whose low 16 bits are stored.

Preserve coordinate bit patterns, field widths, field order and angle encoding. This is not the larger `SaveSessionCheckpoint` snapshot. Copying a host structure or converting the coordinates through floating point is not equivalent to the packed-bit contract.

## Callback/address adapter

`InvokeOptionalCallbackAndComplementAddress` is ov001 ARM entry `020613e0`. It calls a non-NULL `void(void)` callback, discards that callback's result and returns the bitwise complement of its **32-bit DS function address**. A NULL input returns `0xffffffff`.

`StartFieldSession` passes this adapter to startup probe routines in overlay 104. The body establishes the call and address arithmetic; it does not establish the return's broader protocol meaning or a success Boolean. The result is not an owned pointer or allocation.

This is an explicitly unresolved host boundary. Complementing a host function pointer, or replacing the result with the callback's return value, does not reproduce the native operation. Recover the caller protocol before choosing a host representation or replacement.

## Evidence and interface limits

Native identity is retained in `eu/config/arm9/overlays/ov001/symbols.txt` and each target overlay's symbol map. EU wrappers in `eu/src/overlays/ov001` establish the region aliases; root-tree include filenames can retain US addresses and obsolete categories. `SetSessionState` and its overlay-ID table establish the bank selection. The target initializer stores and the shared consumers listed above establish the callback fields.

Logical signatures in this document explain the recovered operations. Erased native function-pointer casts, legacy unused argument slots, DS address words and partial padded structures are separate compatibility details. They must not become invented public parameters, complete host object definitions or ownership promises.

## Reproduction

The ov036 identity correction is also recorded in
[OVERLAY_IDENTITY_BINDINGS.md](OVERLAY_IDENTITY_BINDINGS.md). The remaining
fourteen functions in this block use the existing compiler/mode selection and
official verifier. Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv028Handlers.c InstallSessionOv028Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv030Handlers.c InstallSessionOv030Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv031Handlers.c InstallSessionOv031Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv035Handlers.c InstallSessionOv035Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv032Handlers.c InstallSessionOv032Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv029Handlers.c InstallSessionOv029Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InstallSessionOv038Handlers.c InstallSessionOv038Handlers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasSessionContext.c HasSessionContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionResourceArchive.c GetSessionResourceArchive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldSessionState.c GetFieldSessionState --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StorePackedSessionPlacement.c StorePackedSessionPlacement --thumb
python tools/verify_idx.py src/overlays/ov001/calls/LoadPackedSessionPlacement.c LoadPackedSessionPlacement --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InvokeOptionalCallbackAndComplementAddress.c InvokeOptionalCallbackAndComplementAddress
python tools/verify_idx.py src/overlays/ov001/auto/GetSessionFlagsMask20.c GetSessionFlagsMask20 --thumb
bash tools/gate.sh
```

Integration preserves baseline objects and compares affected production texts,
resolved relocation targets/types and addends before requiring unchanged hashes
for all 108 linked modules. Callback meanings and lifetimes are established
separately from the instruction comparison.
