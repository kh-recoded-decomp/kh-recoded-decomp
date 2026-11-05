# File-load queue task

[FILE_LOADER.md](FILE_LOADER.md) documents the separate main-loader queue,
allocation direction and wait semantics.

The overlay-27 queue task keeps pending and completed intrusive lists in its
24-byte task work. `FileLoadQueue.h` now supplies the common request/work
layout for the EU initializer, processor, allocation, destruction and shutdown
operations. All layouts in that header describe the DS ABI.

## Names and evidence

| Previous symbol | Current name | Evidence |
|---|---|---|
| `func_ov027_020ba060` (`0x020ba060`) | `InitFileLoadQueueTask` | Stores current task work, clears 24 bytes, initializes two lists and returns the processor callback. |
| `func_ov027_020ba124` (`0x020ba124`) | `UpdateFileLoadQueueTask` | Calls `ProcessFileLoadQueue` and returns zero. The included shared source's display-session type did not describe this EU binding. |
| `func_ov027_020ba1f8` (`0x020ba1f8`) | `GetFileLoadRequestBuffer` | Returns request word `+0x08`. Allocation/processing place the file buffer there, destruction frees it when requested, and resource consumers pass it to unpackers. |
| `data_ov027_020ba3b4` (`0x020ba3b4`) | `gFileLoadQueueTaskDescriptor` | Its first five words contain IDs `0x000e0012`, the initializer, shutdown callback, work size `0x18` and a null heap reference. The field HUD passes it to the task constructor. |
| `data_ov027_020ba3e4` (`0x020ba3e4`) | `gFileLoadQueueStateWords` | The first stored word is the work address used by queue operations; the original source owns seven words here, and the other six have no established use. |

The descriptor owns 44 source bytes, although only its first 20 bytes have an
established descriptor interpretation. Its six trailing zero words remain
unchanged. Similarly, the seven-word BSS storage span does not prove a
seven-field runtime state structure. The header preserves these spans and
interprets only the established work-address word. It does not assign meanings
to unreferenced words or silently fold them into the 24-byte task work.

## Recovered layouts

Each 12-byte list header contains a head pointer at `+0x00`, tail pointer at
`+0x04`, 16-bit object count at `+0x08` and 16-bit link offset at `+0x0a`.
`FileLoadQueueWork` contains `pending` at `+0x00` and `completed` at `+0x0c`.
The initializer sets each list's link offset to `0x18`.

| Request offset | Type | Established use |
|---|---|---|
| `0x00` | `s32` | State: zero initially, one after submitting a load, two after completion. |
| `0x04` | `char *` | Owned path copy, or a numeric file ID encoded with bit 31 set. |
| `0x08` | `void *` | File buffer address, also used as the loader's activity key. |
| `0x0c` | `s32` | Load mode; zero/nonzero chooses the existing loader wrapper. |
| `0x10` | `void *` | Caller data forwarded to the completion callback. |
| `0x14` | callback pointer | Called with `(request, userData)` after completion. |
| `0x18` | two pointers | Intrusive previous/next links. |
| `0x20` | four bytes | Cleared with the 36-byte request; meaning unresolved. |

The buffer/activity-key interpretation follows the lower-level loader too:
`RequestFileLoadFromHeapHead` and `RequestFileLoadFromHeapTail` forward to `RequestFileLoad`, which allocates
the destination buffer before queueing the read and returns that buffer's DS
address. `IsRecordIdFree` searches active and queued loader handles for that
address at handle offset `0x28`. The request's word `+0x08` is therefore not an
unrelated numeric request ID or a pointer to the loader handle.

## Lifecycle and behavior

1. The task system allocates work; the initializer stores its address and
   initializes both lists. Its constructor argument is real but ignored here.
2. `QueueFileLoadRequest` allocates and clears a 36-byte request. For a path,
   it allocates a private string copy. A bit-31-tagged file ID is retained
   without copying or dereferencing it as text. The new request is appended to
   `pending` with state zero.
3. `ProcessFileLoadQueue` handles only the first pending request on a call. It
   returns early while either `gPanelActive` or `gPreviousPanelActive` is set.
   In state zero it waits for the loader-idle predicate, submits the selected
   load wrapper with value 14 and records state one. It does not also execute
   the state-one case on that call.
4. In state one, once the buffer/activity key is no longer active, processing
   stores state two, moves the request to `completed`, then calls its callback
   if present. There is no access to the request after the callback returns;
   established callbacks can destroy/release the completed request there.
5. `DestroyFileLoadRequest` removes the request from `completed`, optionally
   frees its buffer, frees an owned path, and frees the request. A tagged file
   ID is cleared rather than freed. With `freeBuffer == FALSE`, the caller
   retains responsibility for the buffer. The routine dereferences the request
   before its final null check, so it does not accept a null request.
6. `ClearOverlayLoadQueues`, the descriptor's shutdown entry, walks pending
   requests using saved next pointers. For state-one requests it calls the
   `SleepIfFileLoaderBusy` helper and frees a non-null buffer. It then unlinks
   and frees pending requests and owned paths. It destroys completed requests
   with buffer release enabled. It does not clear the retained work address.

`IsFileLoadQueueEmpty` tests only `pending`; completed requests may still exist.
If there is no work address it returns **FALSE**, not TRUE. This is not a general
all-resources-released predicate. The getter merely returns the buffer; it does
not check completion or transfer ownership. Allocation/processing have no new
failure-recovery branch if a lower-level allocator or load submission fails;
these contracts must be established separately before changing host behavior.

## C declarations and port boundary

The former getter source declared four generic integer arguments although only
the request address was used. It now declares the evidenced request pointer
and returns its buffer pointer. Two EU resource consumers previously called an
unprototyped getter with no written argument, relying on the request remaining
in r0. They now pass that request explicitly and still reproduce the same
instructions. Shared-source consumers retain their established DS integer
return views through EU symbol aliases; a host port should update those
signatures together with its resource APIs.

Replace the stored 32-bit work address with a host pointer in a host port. Use
one consistent request/list/callback definition. Represent tagged numeric file
IDs separately from host pointers: testing a 64-bit host pointer's bit 31 would
not reproduce this DS resource encoding. Keep the two list lifetimes,
callback-after-move order, path/buffer ownership and single-request processing
behavior explicit. Establish task work lifetime before reading the retained
address after shutdown. The six unassigned BSS words and descriptor tail stay
unresolved, rather than becoming guessed host fields.

## Reproduction

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov027/calls/InitFileLoadQueueTask.c InitFileLoadQueueTask --thumb
python tools/verify_idx.py src/overlays/ov027/calls/UpdateFileLoadQueueTask.c UpdateFileLoadQueueTask
python tools/verify_idx.py src/overlays/ov027/calls/GetFileLoadRequestBuffer.c GetFileLoadRequestBuffer
python tools/verify_idx.py src/overlays/ov027/calls/QueueFileLoadRequest.c QueueFileLoadRequest
python tools/verify_idx.py src/overlays/ov027/calls/ProcessFileLoadQueue.c ProcessFileLoadQueue --thumb
python tools/verify_idx.py src/overlays/ov027/calls/IsFileLoadQueueEmpty.c IsFileLoadQueueEmpty
python tools/verify_idx.py src/overlays/ov027/calls/DestroyFileLoadRequest.c DestroyFileLoadRequest
python tools/verify_idx.py src/overlays/ov027/calls/ClearOverlayLoadQueues.c ClearOverlayLoadQueues --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_02078cf8.c func_ov001_02078cf8 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_02078d7c.c func_ov001_02078d7c --thumb
bash tools/gate.sh
```

The ten function sizes are 52, 16, 8, 140, 148, 56, 124, 144, 42 and 92 bytes.
The official fresh linked gate must pass all 108 modules, including DATA layout
and every shared-source reference. Naming and type recovery do not add C bytes.
