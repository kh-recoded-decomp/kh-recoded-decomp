"""NitroSDK memory copy and fill kernels (ITCM byte move/fill, word clear/copy/send).

Each model below is the C-level contract of the routine: memcpy/memmove/memset
on bytes, or the SDK's word loops. Every case fills a 4 KB window at SCRATCH
with random bytes, runs the routine, and compares the whole window, so any byte
written outside the destination (a guard byte) is caught. Register results are
the pointers the routine leaves behind, which the byte-move pieces hand to one
another; r4-r11 and sp must come back unchanged.
"""

from arm_exec import Memory
from verify_sdklib import SCRATCH, STACK_TOP, Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_memory.md"
WINDOW = 0x1000
GXFIFO = 0x04000400          # geometry command FIFO, a write-only I/O port


# -- models ---------------------------------------------------------------------
def move_bytes(mem: bytearray, src: int, dst: int, n: int) -> None:
    """memmove: the destination receives the source bytes as they were before the call."""
    mem[dst:dst + n] = bytes(mem[src:src + n])


def fill_bytes(mem: bytearray, dst: int, value: int, n: int) -> None:
    """memset with an unsigned-char value."""
    mem[dst:dst + n] = bytes([value]) * n


def word_count(size: int) -> int:
    """The word loops run while the pointer is below start + size, so a partial word counts."""
    return (size + 3) // 4


def fill_words(mem: bytearray, dst: int, value: int, size: int) -> None:
    mem[dst:dst + 4 * word_count(size)] = value.to_bytes(4, "little") * word_count(size)


def copy_words(mem: bytearray, src: int, dst: int, size: int) -> None:
    """Ascending word copy; equal to memmove when the destination is below the source."""
    for i in range(word_count(size)):
        mem[dst + 4 * i:dst + 4 * i + 4] = mem[src + 4 * i:src + 4 * i + 4]


# -- case plumbing --------------------------------------------------------------
def window_case(rng, args, expect, regs, label):
    """Random window, routine run on it, whole window compared with `expect(window)`."""
    before = bytearray(rng.randbytes(WINDOW))
    after = bytearray(before)
    expect(after)

    def setup(mem: Memory) -> None:
        buf, off = mem._find(SCRATCH, WINDOW)
        buf[off:off + WINDOW] = before

    def check(cpu) -> str | None:
        got = cpu.mem.bytes(SCRATCH, WINDOW)
        if got != after:
            bad = next(i for i in range(WINDOW) if got[i] != after[i])
            return "byte at +0x%x = 0x%02x, model 0x%02x" % (bad, got[bad], after[bad])
        return saved_registers(cpu)

    return Case(args, regs=regs, setup=setup, check=check, label=label)


def saved_registers(cpu) -> str | None:
    for reg in range(4, 12):
        if cpu.r[reg] != 0:
            return "r%d not preserved" % reg
    if cpu.r[13] != STACK_TOP:
        return "sp not restored"
    return None


def lengths(rng, low=0, high=256, extra=300, top=0x600):
    yield from range(low, high + 1)
    for _ in range(extra):
        yield rng.randrange(high + 1, top)


# -- byte move ------------------------------------------------------------------
def placements(rng, n, direction):
    """(src, dst) window offsets: disjoint for every alignment pair, then overlaps in `direction`."""
    room = WINDOW - n - 0x40
    for sa in range(4):
        for da in range(4):
            if n > 64 and (sa, da) not in ((0, 0), (1, 3), (2, 1), (3, 2)) and rng.random() < 0.5:
                continue
            half = room // 2
            src = 0x10 + 4 * rng.randrange(max(1, half // 4 - n // 4)) + sa
            dst = src + n + 0x10 + 4 * rng.randrange(1, 4) + ((da - sa - n - 0x10) & 3)
            if dst + n > WINDOW - 0x10:
                continue
            yield (src, dst) if rng.random() < 0.5 else (dst, src)
    if n == 0:
        return
    for _ in range(3):
        delta = rng.randrange(1, n + 5)
        src = 0x20 + rng.randrange(0x40)
        if direction > 0:          # destination below the source
            yield src + delta, src
        else:                      # destination above the source
            yield src, src + delta


def memmove_cases(rng, forward_only):
    for n in lengths(rng):
        for src, dst in placements(rng, n, +1):
            if forward_only and src < dst < src + n:
                continue
            yield move_case(rng, src, dst, n, forward_only)
        if not forward_only:
            for src, dst in placements(rng, n, -1):
                if src < dst < src + n or dst == src:
                    yield move_case(rng, src, dst, n, False)
    if not forward_only:
        for n in (0, 1, 9, 64, 300):            # source equals destination
            yield move_case(rng, 0x101, 0x101, n, False)


def move_case(rng, src, dst, n, forward_only):
    a, b = SCRATCH + src, SCRATCH + dst
    if n == 0 or a == b:
        regs = {0: a, 1: b}
    elif forward_only or a > b:
        regs = {0: a + n, 1: b + n}
    else:
        regs = {0: a, 1: b}
    return window_case(rng, (a, b, n), lambda m: move_bytes(m, src, dst, n), regs,
                       "src+%d dst+%d n=%d" % (src & 3, dst & 3, n))


def copy_entry_cases(rng):
    return memmove_cases(rng, True)


def move_entry_cases(rng):
    return memmove_cases(rng, False)


def piece_cases(rng, offset, backward, minimum):
    """A move piece: r0 = word-aligned source pointer, r1 = destination pointer rounded down
    to a word, the real destination being r1 + offset. Forward pieces take start pointers,
    backward pieces end pointers (one past the last byte)."""
    for n in lengths(rng, minimum, 256, 200, 0x500):
        for overlap in (False, False, n > 0):
            # forward pieces take start pointers, backward pieces end pointers
            src = (0x700 if backward else 0x100) + 4 * rng.randrange(0x40)
            if overlap:
                gap = rng.randrange(1, n + 8)
                dst = ((src + gap if backward else src - gap) & ~3) + offset
                if (dst < src) == backward or dst == src:
                    continue
            else:
                side = n + 0x20 + 4 * rng.randrange(8)
                dst = ((src + side if rng.random() < 0.5 else src - side) & ~3) + offset
            s, d = (src - n, dst - n) if backward else (src, dst)
            if min(s, d) < 0x10 or max(s, d) + n > WINDOW - 0x10:
                continue
            regs = {0: SCRATCH + s, 1: SCRATCH + d} if backward else {0: SCRATCH + s + n, 1: SCRATCH + d + n}
            yield window_case(rng, (SCRATCH + src, (SCRATCH + dst) & ~3, n),
                              lambda m, s=s, d=d, n=n: move_bytes(m, s, d, n), regs,
                              "piece src+0x%x dst+0x%x n=%d" % (src, dst, n))


def forward_piece(offset, minimum):
    return lambda rng: piece_cases(rng, offset, False, minimum)


def backward_piece(offset, minimum):
    return lambda rng: piece_cases(rng, offset, True, minimum)


def tail_cases(rng, backward):
    """r2 & 7 bytes, any alignment; bits above 2 of r2 are ignored."""
    for count in list(range(8)) * 24 + [rng.getrandbits(32) for _ in range(200)]:
        n = count & 7
        src = 0x40 + rng.randrange(0x400)
        dst = 0x500 + rng.randrange(0x400)
        if rng.random() < 0.5:
            src, dst = dst, src
        if backward:
            args = (SCRATCH + src + n, SCRATCH + dst + n, count)
            regs = {0: SCRATCH + src, 1: SCRATCH + dst, 2: count}
        else:
            args = (SCRATCH + src, SCRATCH + dst, count)
            regs = {0: SCRATCH + src + n, 1: SCRATCH + dst + n, 2: count}
        yield window_case(rng, args, lambda m, s=src, d=dst, n=n: move_bytes(m, s, d, n), regs,
                          "tail r2=0x%x" % count)


# -- byte fill ------------------------------------------------------------------
def fill_cases(rng):
    for n in lengths(rng):
        for align in range(8):
            if n > 64 and rng.random() < 0.6:
                continue
            dst = 0x20 + 8 * rng.randrange(0x40) + align
            value = rng.choice((0, 0xFF, 0x80, 0x01, rng.getrandbits(8)))
            yield window_case(rng, (SCRATCH + dst, value, n),
                              lambda m, d=dst, v=value, n=n: fill_bytes(m, d, v, n),
                              {0: SCRATCH + dst + n}, "fill +%d n=%d" % (align, n))


# -- word kernels ----------------------------------------------------------------
def word_sizes(rng):
    yield from range(0, 257)
    for _ in range(250):
        yield rng.randrange(257, 0x700)


def clear_cases(rng):
    """value r0, destination r1 (word-aligned), size r2 in bytes."""
    for size in word_sizes(rng):
        value = rng.choice((0, MASK, rng.getrandbits(32)))
        dst = 0x10 + 4 * rng.randrange((WINDOW - 0x720) // 4)
        yield window_case(rng, (value, SCRATCH + dst, size),
                          lambda m, d=dst, v=value, s=size: fill_words(m, d, v, s),
                          {0: value, 1: SCRATCH + dst + 4 * word_count(size)}, "size=%d" % size)


def copy_cases(rng):
    """source r0, destination r1 (both word-aligned), size r2 in bytes; overlap only downward."""
    for size in word_sizes(rng):
        span = 4 * word_count(size)
        for overlap in (False, size % 7 == 0):
            if overlap and span:
                dst = 0x20 + 4 * rng.randrange(0x40)
                src = dst + 4 * rng.randrange(1, span // 4 + 2)
            else:
                src = 0x10 + 4 * rng.randrange(0x40)
                dst = src + span + 4 * rng.randrange(1, 0x40)
                if rng.random() < 0.5:
                    src, dst = dst, src
            if max(src, dst) + span > WINDOW:
                continue
            yield window_case(rng, (SCRATCH + src, SCRATCH + dst, size),
                              lambda m, s=src, d=dst, z=size: copy_words(m, s, d, z),
                              {0: SCRATCH + src + span, 1: SCRATCH + dst + span}, "size=%d" % size)


def send_cases(rng):
    """source r0 (word-aligned), fixed port address r1, size r2: every word goes to the port."""
    for size in word_sizes(rng):
        src = 0x10 + 4 * rng.randrange((WINDOW - 0x720) // 4)
        data = rng.randbytes(WINDOW)
        words = [int.from_bytes(data[src + 4 * i:src + 4 * i + 4], "little") for i in range(word_count(size))]
        log = []

        def setup(mem, data=data, log=log):
            if not any(lo <= GXFIFO < hi for lo, hi, _ in mem.regions):
                mem.map(GXFIFO, size=4)
            mem.__dict__.pop("write", None)
            buf, off = mem._find(SCRATCH, WINDOW)
            buf[off:off + WINDOW] = data

            def logged(address, width, value):
                log.append((address, width, value & MASK))
                Memory.write(mem, address, width, value)
            mem.write = logged

        def check(cpu, data=data, log=log, words=words):
            cpu.mem.__dict__.pop("write", None)
            if log != [(GXFIFO, 4, w) for w in words]:
                return "port received %d writes, model %d words" % (len(log), len(words))
            if cpu.mem.bytes(SCRATCH, WINDOW) != data:
                return "memory outside the port changed"
            return saved_registers(cpu)

        yield Case((SCRATCH + src, GXFIFO, size),
                   regs={0: SCRATCH + src + 4 * len(words), 1: GXFIFO},
                   setup=setup, check=check, label="size=%d" % size)


ROUTINES = [
    Routine("func_01ff8ad8", "src/asm_stubs/calls/func_01ff8ad8.c", DOC, copy_entry_cases, object_gate=True),
    Routine("func_01ff8b7c", "src/asm_stubs/calls/func_01ff8b7c.c", DOC, forward_piece(0, 0)),
    Routine("func_01ff8bb8", "src/asm_stubs/calls/func_01ff8bb8.c", DOC, forward_piece(1, 4)),
    Routine("func_01ff8c50", "src/asm_stubs/calls/func_01ff8c50.c", DOC, forward_piece(2, 4)),
    Routine("func_01ff8ce8", "src/asm_stubs/calls/func_01ff8ce8.c", DOC, forward_piece(3, 4)),
    Routine("func_01ff8d80", "src/asm_stubs/calls/func_01ff8d80.c", DOC, lambda rng: tail_cases(rng, False)),
    Routine("func_01ff8dc8", "src/asm_stubs/calls/func_01ff8dc8.c", DOC, move_entry_cases, object_gate=True),
    Routine("func_01ff8e84", "src/asm_stubs/calls/func_01ff8e84.c", DOC, backward_piece(0, 0)),
    Routine("func_01ff8ec0", "src/asm_stubs/calls/func_01ff8ec0.c", DOC, backward_piece(1, 4)),
    Routine("func_01ff8f5c", "src/asm_stubs/calls/func_01ff8f5c.c", DOC, backward_piece(2, 4)),
    Routine("func_01ff8ff8", "src/asm_stubs/calls/func_01ff8ff8.c", DOC, backward_piece(3, 4)),
    Routine("func_01ff9094", "src/asm_stubs/calls/func_01ff9094.c", DOC, lambda rng: tail_cases(rng, True)),
    Routine("func_01ff88c4", "src/asm_stubs/calls/func_01ff88c4.c", DOC, fill_cases),
    Routine("MIi_CpuClear32", "libs/nitro/mi/asm_stubs/auto/MIi_CpuClear32.c", DOC, clear_cases),
    Routine("MIi_CpuCopy32", "libs/nitro/mi/asm_stubs/auto/MIi_CpuCopy32.c", DOC, copy_cases),
    Routine("MIi_CpuSend32", "libs/nitro/mi/asm_stubs/auto/MIi_CpuSend32.c", DOC, send_cases),
    Routine("MIi_CpuClearFast", "libs/nitro/mi/asm_stubs/auto/MIi_CpuClearFast.c", DOC, clear_cases),
    Routine("MIi_CpuCopyFast", "libs/nitro/mi/asm_stubs/auto/MIi_CpuCopyFast.c", DOC, copy_cases),
    Routine("func_0200093c", "libs/nitro/os/asm_stubs/auto/func_0200093c.c", DOC, clear_cases),
    Routine("func_01ff840c", "libs/nitro/os/asm_stubs/auto/func_01ff840c.c", DOC, clear_cases),
]
