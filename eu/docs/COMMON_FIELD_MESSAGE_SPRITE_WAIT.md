# Common field message-sprite activation and script wait

This block names three existing functions from the manager's actual field
writers, projection/draw dispatch and script protocol. The old loader labels
do not establish asynchronous loading readiness.

| EU identity | Previous name | Name | EU source |
|---|---|---|---|---|
| ov001:0x0206cb20 (Thumb, 24 B) | `func_ov001_0206cb20` | `IsCommonFieldMessageSpriteActive` | `eu/src/overlays/ov001/calls/IsCommonFieldMessageSpriteActive.c` |
| ov001:0x02065a70 (Thumb, 36 B) | `func_ov001_02065a70` | `ScriptCmd_BeginCommonFieldMessageSpriteWait` | `eu/src/overlays/ov001/calls/ScriptCmd_BeginCommonFieldMessageSpriteWait.c` |
| ov001:0x02065a94 (Thumb, 48 B) | `func_ov001_02065a94` | `ScriptCmd_AdvanceCommonFieldMessageSpriteWait` | `eu/src/overlays/ov001/calls/ScriptCmd_AdvanceCommonFieldMessageSpriteWait.c` |

The owner is `gFieldMessageSpriteManager` at 0x020a04b8: a 0xa4-byte manager with
a control word, common 0x28-byte record at +4, and three localized records.
`InitMessageLoaders` loads the common ba/ef/info sprite resources and localized
resources through `LoadAnimSetSlots`, then registers `RefreshMenuWindows`.
The initial common active/state byte at record+0x11 is 0. The predicate compares
that same byte, manager+0x15, with exactly 1; it requires an initialized manager.

`ConfigureChannelSlot(0,1,0)` selects the common record and sets target index+0x10
=0, active+0x11=1, frame/value+0x12=1 and elapsed+0x14=0. Its value 0 path clears
activation. `UpdateAllTrackedProbes` sends these records to
`UpdateTrackedTargetMarker`, which obtains the target actor's position, projects
it to screen, sets the draw-hit flag, increments elapsed and clears active
when elapsed reaches 0x3000. `RefreshMenuWindows` sends the same records to
`FlushScrolledEntryPosition`, which selects entry[frame-1], applies the projected
base position plus its existing X offset, draws it and clears the draw-hit flag. These
are the same physical records; they do not need a new layout or IO-state enum.

The field script pair is group 2/entry 0x46, flat pointers 140/141, native words
02065a71/02065a95. Neither handler decodes operands. On run, an already-active
common sprite returns 1 immediately. Otherwise it resets the wait counter,
calls `SetFieldEntriesPaused(1)` and returns 0. Each resume reactivates the
common sprite with `(0,1,0)`, increments the signed counter, and returns 1 after
clearing it at count>=15; earlier resumes return0. This is 15 resume invocations,
not a proven duration in milliseconds or a guarantee of one call per frame.
The resume does not recheck readiness and does not unpause the field actors.

The counter is not a nested VM. `ScriptVm_Start` stores its third argument,
the caller-supplied extra/work context, at VM+0x1c8. `OpenSessionArchive` passes
archive+0x648 (its workArea) as the fourth argument of RoundAndInitArchive,
which forwards it as ScriptVm_Start's extra. Thus extra+0x1c8 is VM/archive
+0x810 on this path. The run/reset and resume/count accesses target that
scratch counter. A full ScriptExtra layout or new public type is unnecessary.
`ScriptVm_RunFrame` keeps the resume callback pending for result 0 and advances
or clears its scheduling slot when result 1 is returned.

The exact old signatures/private views stay: run `u32(s32 entry)` and resume
`BOOL(RetryContext*)`; the predicate is `BOOL(void)`. No new parameter, context
structure, lifetime, image meaning or frame timing is invented. The requested
frame/value 1 and target index 0 remain literal values; the names describe the
common field message-sprite wait operation rather than a narrative icon.


The 15-function native review establishes these same records, the VM extra-context chain and both script-table words. [SubScene9](SUBSCENE9_REQUEST_CONTRACT.md) is a separate owner and request protocol.

## Byte-exact validation

All ten affected official function checks pass. All 12 complete objects preserve allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Source bodies, signatures and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/IsCommonFieldMessageSpriteActive.c IsCommonFieldMessageSpriteActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_BeginCommonFieldMessageSpriteWait.c ScriptCmd_BeginCommonFieldMessageSpriteWait --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_AdvanceCommonFieldMessageSpriteWait.c ScriptCmd_AdvanceCommonFieldMessageSpriteWait --thumb
bash tools/gate.sh
```
