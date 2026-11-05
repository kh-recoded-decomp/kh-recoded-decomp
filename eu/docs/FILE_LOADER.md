# Main file loader: allocation, messages and waiting

The main loader accepts file reads and audio/streaming commands on the same
Nitro OS message queue. It is separate from the overlay-27 request-list task
in [FILE_LOAD_QUEUE.md](FILE_LOAD_QUEUE.md).

## Recovered names

| Previous name | Current name | Evidence |
|---|---|---|
| `func_0202c378` (`0x0202c378`) | `RequestFileLoadFromHeapHead` | Calls `RequestFileLoad` with allocation selector zero. Both plain and compressed paths allocate the destination with positive `0x20` alignment; the expanded-heap allocator dispatches nonnegative alignment to `AllocFromHead`. |
| `func_0202c38c` (`0x0202c38c`) | `RequestFileLoadFromHeapTail` | Uses selector one. Both paths use `-0x20` alignment, which the heap allocator dispatches to `AllocFromTail` with magnitude `0x20`. |
| `func_0202c44c` (`0x0202c44c`) | `SleepIfFileLoaderBusy` | Checks pending message count and the reader's current request, sleeps on the reader's wait queue when busy, then returns one. |
| `data_02060584` (`0x02060584`) | `gFileLoaderMessageQueue` | Initialized by `OS_InitMessageQueue`, written by file/audio request producers, read by the loader thread and inspected by `IsRecordIdFree`. |
| `data_020605a4` (`0x020605a4`) | `gFileLoaderThreadStorage` | Passed to `OS_CreateThread` and `OS_WakeupThreadDirect`. Its original 192-byte word storage is retained; this does not establish all OSThread fields. |
| `data_02060664` (`0x02060664`) | `gFileLoaderMessages` | 64 pointer slots passed as queue backing storage with capacity `0x40`. |

Allocation-direction names describe the destination buffer in both load paths.
They do not mean the worker consumes messages in opposite orders, or that
submission waits for the read to finish. `RequestFileLoad` allocates the buffer
before queuing its private loader handle and returns the buffer's address.
Its plain path uses `AllocFromHeapOrDefaultEx`; its compressed path uses
`PrepareCompressedLoad`, which applies the same allocation selector.

## Message-queue layout

`src/filesystem/FileLoaderState.h` records the 32-byte DS queue view used by
the initializer and the existing activity query. The source-owned queue,
thread storage and backing table keep their original sizes and alignments.

| Queue offset | Size | Established use |
|---|---:|---|
| `0x00` | 8 | Sender wait queue: head and tail pointers. |
| `0x08` | 8 | Receiver wait queue: head and tail pointers. |
| `0x10` | 4 | Pointer to the message-slot table. |
| `0x14` | 4 | Capacity, initialized to 64. |
| `0x18` | 4 | Ring head index. |
| `0x1c` | 4 | Pending message count. |

`OS_InitMessageQueue` establishes all eight words. `OS_ReceiveMessage` sleeps
on `+0x08` while empty, reads `table[head]`, advances head modulo capacity,
decrements the count and wakes senders at `+0x00`. The header retains the
unsigned index/count view already used by `IsRecordIdFree`; it does not claim
to replace the SDK's complete public type system.

The queue begins at `gFileLoader + 0x20`, so its pending count is the same word
as the partial loader views at `gFileLoader + 0x3c`. In the shared worker source
that word is labelled `hold`; its queue-count identity is established by the
address and OS initialization/receive accesses. It is not evidence of another
independent hold flag. Current source storage is split across several global
objects: a host port should define one coherent state instead of copying a
legacy partial view's `sizeof` over adjacent objects.

## Activity query and wait semantics

The loader reader pointer is at `gFileLoader + 0x04`. Its current private
request pointer is at reader offset `0x448`; its eight-byte idle wait queue
starts at `0x44c`.

`IsRecordIdFree(0)` returns true only when the message queue is empty and the
reader's current request pointer is null. For a nonzero argument it checks
request word `+0x28` in the active request and every queued non-null request,
walking the ring in logical order. It returns true if that key is absent.
For file requests this word is the destination buffer address. A key's absence
alone is not a successful-read result, an ownership transfer or proof that a
caller ever submitted that key.

`SleepIfFileLoaderBusy` calls `OS_SleepThread(reader + 0x44c)` if the signed
pending-count view is positive or a current request exists. Otherwise it
returns immediately. Both paths return one. There is one conditional sleep;
the function does not loop to recheck the predicate and does not report a
read status through its return value.

The worker wakes the reader's waiters at the top of its receive state when the
pending count is zero, then clears the current request before receiving the
next message. Preserve this ordering and the scheduler contract when examining
native races; do not silently turn the helper into a polling loop. Some
callers, such as `AllocLoaderRequest`, already provide their own retry loop.
The query itself adds no interrupt masking or host synchronization.

## Worker and lifetime

`InitFileLoader` initializes the queue with its persistent backing table,
initializes the reader's idle wait queue and starts the worker in its existing
thread storage. The worker's private handles distinguish plain file loads,
compressed file loads and audio/streaming commands. The `QueueTypedMessage`
family uses the same queue as `RequestFileLoad`. Receiving a null request
terminates the worker; its presence in the ring is not an ordinary file buffer.

The file buffer and private loader handle have distinct lifetimes. The worker
returns completed handles to the loader pool; a client remains responsible for
its file buffer under its own request/cache contract. The message-slot table
and thread storage are global DS storage, not payload allocations released by
an overlay-27 request destructor.

## ABI and host-port boundaries

The three renamed function bindings keep their original compiled interfaces.
The shared heap-direction wrapper sources currently expose four integer
parameter slots and forward the first, second and fourth words, whereas
several established callers express only the two logical inputs. This block
does not invent extra arguments or meanings to normalize those legacy views.
Before exposing a host API, recover and unify the required inputs through
`RequestFileLoad` and `PrepareCompressedLoad`; do not copy inconsistent DS
prototypes into a host build. The head/tail names depend on the explicit
allocation selector and allocator behavior, not on those unresolved words.

Use a host queue, real thread object and pointers sized for the host. Do not
reinterpret the 192 bytes of DS thread storage as an arbitrary host OSThread,
or store 64-bit pointers in DS word layouts. Preserve the distinction between
message occupancy, active work, a buffer-key query and read success. Provide
host synchronization according to the port's scheduler, and keep buffer
ownership explicit across file, cache and audio consumers.

The shared-region wrappers retain original US macro names and include paths
while binding their right-hand references to EU symbols. In particular, the US
`func_0202c38c` name maps to EU `IsRecordIdFree`; it must not be mistaken for the
EU heap-tail wrapper simply because the numeric identifier is the same.

## Reproduction

From `eu/`:

```sh
python tools/verify_idx.py src/calls/RequestFileLoadFromHeapHead.c RequestFileLoadFromHeapHead
python tools/verify_idx.py src/calls/RequestFileLoadFromHeapTail.c RequestFileLoadFromHeapTail
python tools/verify_idx.py src/calls/SleepIfFileLoaderBusy.c SleepIfFileLoaderBusy
python tools/verify_idx.py src/calls/IsRecordIdFree.c IsRecordIdFree
python tools/verify_idx.py src/calls/ByteCode_ExecuteLoadOp.c ByteCode_ExecuteLoadOp --thumb
python tools/verify_idx.py src/calls/InitFileLoader.c InitFileLoader
python tools/verify_idx.py src/calls/FileLoader_ThreadMain.c FileLoader_ThreadMain
python tools/verify_idx.py src/overlays/ov027/calls/ProcessFileLoadQueue.c ProcessFileLoadQueue --thumb
python tools/verify_idx.py src/overlays/ov027/calls/ClearOverlayLoadQueues.c ClearOverlayLoadQueues --thumb
bash tools/gate.sh
```

Those functions retain 20, 20, 64, 172, 108, 344, 928, 148 and 144 bytes. The
fresh linked gate must also preserve the DATA layout and all shared callers
across 108 modules. Naming/type recovery adds no C reconstruction credit.
