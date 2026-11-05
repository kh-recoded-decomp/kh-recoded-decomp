# Captured touch task and DS record

The overlay-27 task stores an eight-byte touch record in its task work. The
names below describe the observed capture/copy/clear behavior, not a new input
policy for a future port.

| EU address | Name | Evidence |
|---|---|---|
| `0x020b9f74` | `InitCapturedTouchTask` | Stores current task work in `gCapturedTouchRecord` and returns the update callback. |
| `0x020b9f8c` | `ShutdownCapturedTouchTask` | The descriptor's shutdown entry; its entire implementation is a Thumb return. |
| `0x020b9f90` | `UpdateCapturedTouchTask` | Calls `CaptureLatestOnScreenTouch` and returns zero. |
| `0x020ba3a0` | `gCapturedTouchTaskDescriptor` | Its initializer, shutdown entry and work size refer to this task. Profile, field-HUD and overlay-39 code pass its address to the task constructor. |
| `0x020ba3e0` | `gCapturedTouchRecord` | Initialized from current task work, filled by capture, read by `CopySourceBlock` and partially cleared by `ClearCapturedTouchState`. This BSS object is a pointer, not the record itself. |

## Layout and descriptor

`src/overlays/ov027/CapturedTouch.h` defines the common DS record and the
five-word descriptor. Size checks require eight bytes for the record and
20 bytes for the descriptor on the DS ABI.

| Record offset | Type | Meaning established by use |
|---|---|---|
| `0x00` | `u16` | X coordinate. |
| `0x02` | `u16` | Y coordinate. |
| `0x04` | `u16` | Touch/contact state; the clear routine writes zero here. |
| `0x06` | `u16` | Invalid indication; the capture scan accepts zero. |

The task descriptor has the ID halves `0x0011` and `0x000e`, initializer and
shutdown pointers, work size eight, and a null heap reference. The meanings of
the ID halves are not inferred from the numeric values. `Obj_Construct` copies
the two halves to its task object, chooses its heap from the reference when
non-null, allocates work according to the recorded size and clears that work
before calling the initializer with the constructor argument. This particular
initializer ignores that argument and only obtains its current task work. The
common descriptor type expresses that real argument explicitly. The profile
and overlay-39 callers now include the same descriptor declaration and pass its
address; they no longer declare it as a byte array or a function. The shared
field-HUD wrapper retains its existing byte-array address view, which is not a
second storage object.

## Selection and copy behavior

`CaptureLatestOnScreenTouch` asks `CopyRecentInputRecords` for records into its
four-record local array. It walks the returned records from newest to oldest,
accepting the first record whose invalid value is zero, X is below 256 and Y
is below 192. If no record meets those conditions and the returned count is
positive, it copies the newest record anyway. With no records it leaves the
previous captured value unchanged. The count/buffer-capacity contract belongs
to the producer; this consumer does not clamp the returned count.

`CopySourceBlock` is the existing public copy operation. It returns zero if
the captured-work pointer is null; otherwise it copies exactly eight bytes to
the caller's destination and returns the destination address. Several legacy
callers express that result as an integer or a pointer. Those are DS ABI views,
not a consistent host-port interface. `ClearCapturedTouchState` writes only the
two-byte touch field: X, Y and invalid remain unchanged. It does not check for
a null captured-work pointer.

## Ownership and port boundary

The task system owns the allocation. The initializer retains a pointer to it;
it does not allocate a second input record. The shutdown callback is empty,
and does not free work or reset the global pointer. A port must preserve the
call ordering or establish the lifetime explicitly before reading the record
after task destruction. Do not treat the null check in `CopySourceBlock` as a
complete lifetime check.

Use one record definition across the capture, copy, clear and consumer APIs in
a host port. Use a pointer return for the copy operation if retaining its
current return convention, and update its declarations together; a 64-bit
pointer cannot be represented by the old DS integer declaration. The DS task
descriptor has pointer-sized fields and is not a host-independent serialized
20-byte format. Do not assign meaning to individual contact/invalid bits
without the input producer's evidence. The adjacent queue-state storage at
`0x020ba3e4` remains outside this type. [FILE_LOAD_QUEUE.md](FILE_LOAD_QUEUE.md)
records its separate seven-word storage span and the established work-address
word, now named `gFileLoadQueueStateWords`.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov027/calls/InitCapturedTouchTask.c InitCapturedTouchTask --thumb
python tools/verify_idx.py src/overlays/ov027/auto/ShutdownCapturedTouchTask.c ShutdownCapturedTouchTask --thumb
python tools/verify_idx.py src/overlays/ov027/calls/UpdateCapturedTouchTask.c UpdateCapturedTouchTask --thumb
python tools/verify_idx.py src/overlays/ov027/calls/CaptureLatestOnScreenTouch.c CaptureLatestOnScreenTouch --thumb
python tools/verify_idx.py src/overlays/ov027/calls/ClearCapturedTouchState.c ClearCapturedTouchState --thumb
python tools/verify_idx.py src/overlays/ov027/calls/CopySourceBlock.c CopySourceBlock --thumb
python tools/verify_idx.py src/overlays/ov002/calls/InitProfilePanel.c InitProfilePanel
python tools/verify_idx.py src/overlays/ov039/calls/InitOverlayState.c InitOverlayState --thumb
python tools/verify_idx.py src/overlays/ov001/calls/CreateFieldHudWidgets.c CreateFieldHudWidgets --thumb
bash tools/gate.sh
```

The six function sizes are 24, 2, 10, 96, 16 and 32 bytes. The three descriptor
callers remain 588, 740 and 376 bytes. The full fresh gate
also checks descriptor relocations, BSS layout, shared-source aliases and all
108 linked modules. Naming and type recovery add no reconstruction credit.
