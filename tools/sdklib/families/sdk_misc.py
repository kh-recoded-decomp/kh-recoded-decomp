"""NitroSDK system routines: divider context, lock IDs, IRQ/exception wrappers, LZ77.

CP_SaveContext / CPi_RestoreContext copy the operands and modes of the
hardware divider and square-root unit to and from a CPContext. The test maps
the unit's I/O block as plain memory, so it checks what the routines move, not
what the hardware computes. OS_GetLockID allocates from the ARM9 lock-ID
bitmap, mapped the same way. The two wrappers are checked by replacing their
callees with small ARM stubs that log every call. MI_ReadUncompLZ8 and
MIi_UncompressBackward are checked on streams made by the compressors below,
written from the format descriptions, never from the decoders.
"""

import struct

from verify_sdklib import SCRATCH, STACK_TOP, Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_misc.md"
SAVED = tuple(0xC0DE0400 + 0x11 * i for i in range(4, 13))      # sentinels for r4..r12
WINDOW = 0x10000


def poke(mem, address: int, data: bytes) -> None:
    buf, off = mem._find(address, len(data))
    buf[off:off + len(data)] = data


def ensure_mapped(mem, start: int, size: int) -> None:
    if not any(lo <= start < hi for lo, hi, _ in mem.regions):
        mem.map(start, size=size)


def preserved(cpu, last=12):
    if cpu.r[4:last + 1] != list(SAVED[:last - 3]):
        return "callee-saved r4-r%d changed" % last
    if cpu.r[13] != STACK_TOP:
        return "sp = 0x%08x after return" % cpu.r[13]
    return None


def first_difference(got: bytes, want: bytes, base: int) -> str | None:
    if got == want:
        return None
    bad = next(i for i in range(len(want)) if got[i] != want[i])
    return "byte at 0x%08x = 0x%02x, model 0x%02x" % (base + bad, got[bad], want[bad])


# -- divider / square-root context ---------------------------------------------------------
IO = 0x04000280             # DIVCNT .. SQRT_PARAM, 0x40 bytes of I/O
DIVCNT, DIV_NUMER, DIV_DENOM, SQRTCNT, SQRT_PARAM = 0x00, 0x10, 0x18, 0x30, 0x38
CONTEXT = 0x1C              # CPContext: u64 div_numer, div_denom, sqrt; u16 div_mode, sqrt_mode


def save_context(io: bytes) -> bytes:
    """The operands as they are, the divide mode (DIVCNT bits 0-1) and the sqrt mode (SQRTCNT bit 0)."""
    div_mode = struct.unpack_from("<H", io, DIVCNT)[0] & 3
    sqrt_mode = struct.unpack_from("<H", io, SQRTCNT)[0] & 1
    return io[DIV_NUMER:DIV_DENOM + 8] + io[SQRT_PARAM:SQRT_PARAM + 8] + struct.pack("<HH", div_mode, sqrt_mode)


def restore_context(context: bytes, io: bytearray) -> None:
    """Every saved field goes back verbatim; the two modes are written as whole halfwords."""
    io[DIV_NUMER:DIV_DENOM + 8] = context[0:16]
    io[DIVCNT:DIVCNT + 2] = context[0x18:0x1A]
    io[SQRTCNT:SQRTCNT + 2] = context[0x1A:0x1C]
    io[SQRT_PARAM:SQRT_PARAM + 8] = context[0x10:0x18]


def io_images(rng):
    yield bytes(0x40)
    yield b"\xff" * 0x40
    for divcnt in range(4):
        for sqrtcnt in (0, 1, 0x8000, 0x8001):
            io = bytearray(rng.randbytes(0x40))
            struct.pack_into("<H", io, DIVCNT, divcnt | (rng.getrandbits(2) << 14))
            struct.pack_into("<H", io, SQRTCNT, sqrtcnt)
            yield bytes(io)
    for _ in range(400):
        yield rng.randbytes(0x40)


def context_case(rng, io_before: bytes, saving: bool):
    ctx = SCRATCH + 0x100 + 4 * rng.randrange(0x100)
    area = ctx - 0x40
    window = bytearray(rng.randbytes(0x40 + CONTEXT + 0x40))
    io_after = bytearray(io_before)
    window_after = bytearray(window)
    if saving:
        window_after[0x40:0x40 + CONTEXT] = save_context(io_before)
    else:
        restore_context(bytes(window[0x40:0x40 + CONTEXT]), io_after)

    def setup(mem):
        ensure_mapped(mem, IO, 0x40)
        poke(mem, IO, io_before)
        poke(mem, area, bytes(window))

    def check(cpu):
        return (first_difference(cpu.mem.bytes(IO, 0x40), bytes(io_after), IO)
                or first_difference(cpu.mem.bytes(area, len(window)), bytes(window_after), area)
                or preserved(cpu, 11))

    return Case((ctx, rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)) + SAVED,
                setup=setup, check=check, label="ctx=0x%08x" % ctx)


def save_cases(rng):
    for io in io_images(rng):
        yield context_case(rng, io, True)


def restore_cases(rng):
    for io in io_images(rng):
        yield context_case(rng, io, False)


# -- lock IDs ---------------------------------------------------------------------------
LOCK_FLAGS = 0x02FFFFB0     # two words, bit set = ID free; MSB of word 0 is ID 0x40
LOCK_AREA = 0x02FFFF80
LOCK_ID_ERROR = -3


def get_lock_id(words: list) -> int:
    """Lowest free ID: word 0 holds 0x40-0x5F, word 1 0x60-0x7F, most significant bit first."""
    for index, first_id in enumerate((0x40, 0x60)):
        if words[index]:
            leading = 32 - words[index].bit_length()
            words[index] &= ~(0x80000000 >> leading) & MASK
            return first_id + leading
    return LOCK_ID_ERROR


def lock_case(rng, words: tuple, label: str):
    area = bytearray(rng.randbytes(0x80))
    struct.pack_into("<II", area, LOCK_FLAGS - LOCK_AREA, *words)
    after = bytearray(area)
    state = list(words)
    result = get_lock_id(state)
    struct.pack_into("<II", after, LOCK_FLAGS - LOCK_AREA, *state)

    def setup(mem):
        ensure_mapped(mem, LOCK_AREA, 0x80)
        poke(mem, LOCK_AREA, bytes(area))

    def check(cpu):
        return first_difference(cpu.mem.bytes(LOCK_AREA, 0x80), bytes(after), LOCK_AREA) or preserved(cpu)

    return Case((rng.getrandbits(32),) * 4 + SAVED, regs={0: result}, setup=setup, check=check, label=label), tuple(state)


def lock_cases(rng):
    for words in ((0, 0), (MASK, MASK), (0, MASK), (MASK, 0), (0, 1), (1, 0), (0x80000000, 0), (0, 0x80000000)):
        yield lock_case(rng, words, "edge")[0]
    for bit in range(32):
        yield lock_case(rng, (1 << bit, rng.getrandbits(32)), "word0 bit %d" % bit)[0]
        yield lock_case(rng, (0, 1 << bit), "word1 bit %d" % bit)[0]
    for start in ((MASK, MASK), (rng.getrandbits(32), rng.getrandbits(32))):
        words = start
        for step in range(66):             # allocate until exhausted, then past it
            case, words = lock_case(rng, words, "sequence step %d" % step)
            yield case
    for _ in range(600):
        dense = rng.random() < 0.5
        sparse = lambda: rng.getrandbits(32) if dense else rng.getrandbits(32) & rng.getrandbits(32) & rng.getrandbits(32)
        first = 0 if rng.random() < 0.3 else sparse()
        yield lock_case(rng, (first, sparse()), "random")[0]


# -- wrappers -----------------------------------------------------------------------------
CALL_LOG = SCRATCH + 0xF000     # u32 count, then {r0, id, sp, lr} per call


def logging_stub(stub_id: int) -> bytes:
    """Callee stand-in: logs r0, its id, sp and lr, then clobbers r0 = ~id and r1-r3, ip = ~0."""
    words = (0xE59FC02C, 0xE59C3000, 0xE08C2203, 0xE3A01000 | stub_id, 0xE9826003, 0xE2833001,
             0xE58C3000, 0xE3E00000 | stub_id, 0xE3E01000, 0xE3E02000, 0xE3E03000, 0xE3E0C000,
             0xE12FFF1E, CALL_LOG)
    return struct.pack("<14I", *words)


def wrapper_model(entry: int, r0: int, callees: list) -> tuple:
    """Each callee in order, with sp 8 bytes lower and lr just past its bl; r0 comes back as passed."""
    sp = STACK_TOP - 8
    log, register = [], r0
    for position, stub_id in enumerate(callees):
        log.append((register, stub_id, sp, entry + 8 + 4 * position))
        register = ~stub_id & MASK
    return log, {0: r0, 1: MASK, 2: MASK, 3: MASK, 12: MASK}


def wrapper_cases(entry: int, callees: tuple):
    def cases(rng):
        for index in range(400):
            r0 = (0, MASK, entry, 0x80000000)[index] if index < 4 else rng.getrandbits(32)
            log, regs = wrapper_model(entry, r0, list(range(1, len(callees) + 1)))

            def setup(mem):
                for stub_id, callee in enumerate(callees, 1):
                    poke(mem, callee, logging_stub(stub_id))
                poke(mem, CALL_LOG, bytes(4 + 16 * 4))
                poke(mem, STACK_TOP - 8, bytes(8))

            def check(cpu, log=log, r0=r0):
                count = cpu.mem.read(CALL_LOG, 4)
                got = [struct.unpack("<4I", cpu.mem.bytes(CALL_LOG + 4 + 16 * i, 16)) for i in range(count)]
                if got != log:
                    return "calls %s, model %s" % (got, log)
                if cpu.mem.bytes(STACK_TOP - 8, 8) != struct.pack("<II", r0, 0xFFFFFFF0):
                    return "stack frame is not {r0, lr}"
                return preserved(cpu, 11)

            yield Case((r0, rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)) + SAVED[:8],
                       regs=regs, setup=setup, check=check, label="r0=0x%08x" % r0)
    return cases


# -- LZ77 (Nintendo type 0x10 / extended 0x11) --------------------------------------------
LZ_CONTEXT = SCRATCH           # MIUncompContextLZ, 0x14 bytes
LZ_INPUT = SCRATCH + 0x40
LZ_OUTPUT = SCRATCH + 0x8000
LZ_OUTPUT_ROOM = 0x7800
CTX_FORMAT = "<IiIHBBBBBB"     # destp, destCount, length, destTmp, destTmpCnt, flags, flagIndex, lengthFlg, exFormat, pad


def find_match(data: bytes, pos: int, table: dict, longest: int, rng, nearest=1, farthest=4096) -> tuple:
    """Longest earlier occurrence (distance nearest..farthest) of the bytes at pos, from a 3-byte hash chain."""
    best_len, best_dist = 0, 0
    for cand in reversed(table.get(data[pos:pos + 3], [])[-48:]):
        dist = pos - cand
        if dist > farthest:
            break
        if dist < nearest:
            continue
        n = 0
        limit = min(longest, len(data) - pos)
        while n < limit and data[cand + n] == data[pos + n]:
            n += 1
        if n > best_len:
            best_len, best_dist = n, dist
    if best_len >= 3 and rng.random() < 0.15:
        best_len = rng.randrange(3, best_len + 1)        # vary the encodings the decoder sees
    return best_len, best_dist


def lz_compress(data: bytes, extended: bool, rng) -> bytes:
    """Flag byte (MSB first, 1 = reference) per eight tokens. A reference is distance-1 in 12 bits
    and a length: 3-18 in the high nibble of the first byte (0x10), or for 0x11 one, two or three
    length bytes selected by that nibble (>=2: length-1; 0: 8 bits of length-0x11; 1: 16 bits of
    length-0x111). The distance's top nibble shares the last length byte."""
    longest = 0x10110 if extended else 18
    out, table, pos = bytearray(), {}, 0
    while pos < len(data):
        flag_at = len(out)
        out.append(0)
        for bit in range(8):
            if pos >= len(data):
                break
            length, dist = find_match(data, pos, table, longest, rng)
            if length >= 3:
                out[flag_at] |= 0x80 >> bit
                d = dist - 1
                if not extended:
                    out += bytes((((length - 3) << 4) | (d >> 8), d & 0xFF))
                elif length <= 16:
                    out += bytes((((length - 1) << 4) | (d >> 8), d & 0xFF))
                elif length <= 0x110:
                    n = length - 0x11
                    out += bytes((n >> 4, ((n & 0xF) << 4) | (d >> 8), d & 0xFF))
                else:
                    n = length - 0x111
                    out += bytes((0x10 | (n >> 12), (n >> 4) & 0xFF, ((n & 0xF) << 4) | (d >> 8), d & 0xFF))
            else:
                length = 1
                out.append(data[pos])
            for p in range(pos, pos + length):
                table.setdefault(data[p:p + 3], []).append(p)
            pos += length
    return bytes(out)


def read_uncomp_lz8(ctx: dict, src: bytes, mem: bytearray, base: int) -> int:
    """Decode as much of the stream as `src` holds into mem (addresses minus `base`).

    The context keeps the stream position between calls: the current flag byte
    and how many of its tokens are left, and for a reference cut off by the end
    of `src`, the length bytes read so far (`length`) and how many are still
    due (`lengthFlg`: 3 = none read yet, 0 = all read, displacement byte next).
    Output stops being counted only between tokens, so a reference running past
    destCount is copied whole and destCount goes negative."""
    pos = 0

    def take() -> int:
        nonlocal pos
        pos += 1
        return src[pos - 1]

    while ctx["destCount"] > 0:
        while ctx["flagIndex"] > 0:
            if pos == len(src):
                return ctx["destCount"]
            if not ctx["flags"] & 0x80:
                mem[ctx["destp"] - base] = take()
                ctx["destp"] += 1
                ctx["destCount"] -= 1
            else:
                while ctx["lengthFlg"]:
                    byte = take()
                    if ctx["exFormat"] != 1:
                        ctx["length"], ctx["lengthFlg"] = byte + 0x30, 0
                    elif ctx["lengthFlg"] == 3:
                        if byte >> 5:
                            ctx["length"], ctx["lengthFlg"] = byte + 0x10, 0
                        elif byte & 0x10:
                            ctx["length"], ctx["lengthFlg"] = 0x1110 + ((byte & 0xF) << 16), 2
                        else:
                            ctx["length"], ctx["lengthFlg"] = 0x110 + ((byte & 0xF) << 8), 1
                    elif ctx["lengthFlg"] == 2:
                        ctx["length"], ctx["lengthFlg"] = ctx["length"] + (byte << 8), 1
                    else:
                        ctx["length"], ctx["lengthFlg"] = ctx["length"] + byte, 0
                    if pos == len(src):
                        return ctx["destCount"]
                distance = (((ctx["length"] & 0xF) << 8) | take()) + 1
                ctx["lengthFlg"] = 3
                for _ in range(ctx["length"] >> 4):
                    at = ctx["destp"] - base
                    mem[at] = mem[at - distance]
                    ctx["destp"] += 1
                    ctx["destCount"] -= 1
                ctx["length"] = 0
            if ctx["destCount"] == 0:
                return 0
            ctx["flags"] = (ctx["flags"] << 1) & 0xFF
            ctx["flagIndex"] -= 1
        if pos == len(src):
            return ctx["destCount"]
        ctx["flags"], ctx["flagIndex"] = take(), 8
    return ctx["destCount"]


def pack_context(ctx: dict, pad: int) -> bytes:
    return struct.pack(CTX_FORMAT, ctx["destp"], ctx["destCount"], ctx["length"] & MASK, ctx["destTmp"],
                       ctx["destTmpCnt"], ctx["flags"], ctx["flagIndex"], ctx["lengthFlg"], ctx["exFormat"], pad)


def sample_data(rng, size: int, style: str) -> bytes:
    if style == "random":
        return rng.randbytes(size)
    if style == "run":
        return bytes([rng.getrandbits(8)]) * size
    if style == "pattern":
        unit = rng.randbytes(rng.randrange(1, 40))
        return (unit * (size // len(unit) + 1))[:size]
    out = bytearray()                       # text-like: pieces copied from earlier output
    while len(out) < size:
        if out and rng.random() < 0.6:
            start = rng.randrange(max(0, len(out) - 4200), len(out))
            n = rng.choice((rng.randrange(3, 20), rng.randrange(17, 300), rng.randrange(1, 6000)))
            for i in range(n):
                out.append(out[start + i])
        else:
            out += bytes(rng.choice(b"aeiou tnsrlKH\x00\xff") for _ in range(rng.randrange(1, 12)))
    return bytes(out[:size])


def lz_stream_cases(rng, data: bytes, extended: bool, dest_count: int, chunks: list | None, label: str):
    """Feed the stream in chunks (random ones when `chunks` is None, plus the rest at the end)."""
    stream = lz_compress(data, extended, rng)
    if chunks is None:
        chunks = chunking(rng, len(stream))
        chunks.append(len(stream) - min(len(stream), sum(chunks)))
    window = bytearray(rng.randbytes(WINDOW))
    destp = LZ_OUTPUT + rng.randrange(4)
    ctx = {"destp": destp, "destCount": dest_count, "length": 0, "destTmp": 0, "destTmpCnt": 0,
           "flags": 0, "flagIndex": 0, "lengthFlg": 3, "exFormat": 1 if extended else 0}
    pad = rng.getrandbits(8)
    pos = 0
    for n in chunks:
        n = min(n, len(stream) - pos)
        chunk = stream[pos:pos + n]
        at = LZ_INPUT + rng.randrange(0x7F00 - n) if n < 0x7F00 else LZ_INPUT
        window[at - SCRATCH:at - SCRATCH + n] = chunk
        window[0:0x14] = pack_context(ctx, pad)
        before = bytes(window)
        remaining = read_uncomp_lz8(ctx, chunk, window, SCRATCH)
        window[0:0x14] = pack_context(ctx, pad)
        after = bytes(window)

        def setup(mem, before=before):
            poke(mem, SCRATCH, before)

        def check(cpu, after=after):
            return first_difference(cpu.mem.bytes(SCRATCH, WINDOW), after, SCRATCH) or preserved(cpu, 11)

        yield Case((LZ_CONTEXT, at, n, rng.getrandbits(32)) + SAVED[:8], regs={0: remaining},
                   setup=setup, check=check, label="%s chunk %d+%d" % (label, pos, n))
        pos += n
    if ctx["destCount"] == 0 and dest_count == len(data):
        got = window[destp - SCRATCH:destp - SCRATCH + len(data)]
        assert got == data, "model failed to reproduce its own compressor's input"


def chunking(rng, total: int) -> list:
    style = rng.choice(("whole", "bytes", "small", "mixed"))
    if style == "whole":
        return [total + rng.randrange(8)]
    if style == "bytes" and total < 300:
        return [1] * (total + 2)
    out, left = [], total
    while left > 0:
        n = rng.randrange(1, 9) if style == "small" else rng.choice((0, 1, 2, 3, rng.randrange(1, 600)))
        out.append(n)
        left -= n
    return out[:400]


def lz_cases(rng):
    for extended in (False, True):
        # degenerate calls: no input, nothing left to write
        yield from lz_stream_cases(rng, b"abc", extended, 3, [0, 0, 1, 0, 1, 1, 1, 1, 5], "len=0 steps")
        yield from lz_stream_cases(rng, b"zz", extended, 0, [2], "destCount=0")
        for size in list(range(1, 40)) + [64, 65, 255, 256, 257]:
            style = rng.choice(("random", "run", "pattern", "text"))
            yield from lz_stream_cases(rng, sample_data(rng, size, style), extended, size,
                                       None, "%s n=%d" % (style, size))
        for size, style in ((18, "run"), (19, "run"), (272, "run"), (273, "run"), (274, "run"),
                            (0x1111, "run"), (0x1112, "run"), (0x7000, "run"), (4500, "pattern")):
            yield from lz_stream_cases(rng, sample_data(rng, size, style), extended, size,
                                       None, "%s n=%d" % (style, size))
        for _ in range(90):
            size = rng.choice((rng.randrange(1, 600), rng.randrange(600, 6000)))
            style = rng.choice(("random", "run", "pattern", "text", "text"))
            data = sample_data(rng, size, style)
            yield from lz_stream_cases(rng, data, extended, size, None, "%s n=%d" % (style, size))
        for _ in range(30):              # destCount short of the stream: the last token overruns it
            size = rng.randrange(40, 3000)
            data = sample_data(rng, size, "text")
            yield from lz_stream_cases(rng, data, extended, rng.randrange(1, size), None,
                                       "short destCount n=%d" % size)


# -- backward LZ (crt0 / overlay "autoload" compression) ------------------------------------
BLZ_BASE = SCRATCH + 0x100


def backward_tokens(reversed_data: bytes, rng) -> tuple:
    """Forward LZ over the reversed data: flag bytes as for LZ77, references as two bytes
    `(length-3) << 4 | (distance-3) >> 8`, `(distance-3) & 0xFF` with distance 3..4098.
    Returns the stream and (bytes produced, bytes consumed) after every token."""
    out, table, pos, marks = bytearray(), {}, 0, [(0, 0)]
    while pos < len(reversed_data):
        flag_at = len(out)
        out.append(0)
        for bit in range(8):
            if pos >= len(reversed_data):
                break
            length, dist = find_match(reversed_data, pos, table, 18, rng, 3, 4098)
            if length >= 3:
                out[flag_at] |= 0x80 >> bit
                out += bytes((((length - 3) << 4) | ((dist - 3) >> 8), (dist - 3) & 0xFF))
            else:
                length = 1
                out.append(reversed_data[pos])
            for p in range(pos, pos + length):
                table.setdefault(reversed_data[p:p + 3], []).append(p)
            pos += length
            marks.append((pos, len(out)))
    return bytes(out), marks


def backward_image(data: bytes, rng, extra_pad: int) -> tuple:
    """In-place image of `data`: an uncompressed head, then the compressed tail stored reversed,
    0xFF padding and the footer {u32 compressed size | footer size << 24, u32 size gain}.

    The tail is cut where the running gain (output minus input so far) peaks, so the
    output pointer never passes the unread input. Returns (image, bottom offset)."""
    stream, marks = backward_tokens(data[::-1], rng)
    produced, consumed = max(marks, key=lambda m: (m[0] - m[1], -m[0]))
    head = data[:len(data) - produced]
    packed = stream[:consumed][::-1]
    pad = (-(len(head) + len(packed)) - (BLZ_BASE & 3)) % 4 + 4 * extra_pad
    footer_size = pad + 8
    region = len(packed) + footer_size
    footer = struct.pack("<II", region | footer_size << 24, (produced - region) & MASK)
    image = head + packed + bytes([0xFF]) * pad + footer
    return image, len(image)


def uncompress_backward(mem: bytearray, base: int, bottom: int) -> list:
    """Decode in place below `bottom` (mem holds addresses from `base`); returns the CP15 ops.

    The output grows downward from bottom + gain while the input is read downward
    from the footer; each reference copies from `distance` bytes above the byte
    being written. Afterwards every 32-byte line from the compressed start to the
    output end gets a write-buffer drain, an I-cache line invalidate and a D-cache
    line clean+invalidate, in that order (at least one line)."""
    if bottom == 0:
        return []
    info, gain = struct.unpack_from("<II", mem, bottom - 8 - base)
    out = (bottom + gain) & MASK
    end = out
    src = bottom - (info >> 24)
    start = bottom - (info & 0xFFFFFF)
    while src > start:
        src -= 1
        flags = mem[src - base]
        for _ in range(8):
            if flags & 0x80:
                high, low = mem[src - 1 - base], mem[src - 2 - base]
                src -= 2
                distance = (((high << 8) | low) & 0xFFF) + 3
                for _ in range((high >> 4) + 3):
                    out -= 1
                    mem[out - base] = mem[out + distance - base]
            else:
                src -= 1
                out -= 1
                mem[out - base] = mem[src - base]
            flags <<= 1
            if src <= start:
                break
    ops, line = [], start & ~31
    while True:
        ops += [(10, 4, 0), (5, 1, line), (14, 1, line)]
        line += 32
        if line >= end:
            return ops


def backward_case(rng, data: bytes, label: str, extra_pad: int = 0, null: bool = False):
    window = bytearray(rng.randbytes(WINDOW))
    if null:
        bottom = 0
    else:
        image, size = backward_image(data, rng, extra_pad)
        window[BLZ_BASE - SCRATCH:BLZ_BASE - SCRATCH + size] = image
        bottom = BLZ_BASE + size
    before = bytes(window)
    ops = uncompress_backward(window, SCRATCH, bottom)
    after = bytes(window)
    if not null:
        assert after[BLZ_BASE - SCRATCH:BLZ_BASE - SCRATCH + len(data)] == data, "image does not decode"

    def setup(mem):
        poke(mem, SCRATCH, before)

    def check(cpu):
        got, cpu.cp15_log = cpu.cp15_log, []
        if got != ops:
            return "%d CP15 ops %s.., model %d %s.." % (len(got), got[:3], len(ops), ops[:3])
        return first_difference(cpu.mem.bytes(SCRATCH, WINDOW), after, SCRATCH) or preserved(cpu, 11)

    return Case((bottom, rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)) + SAVED[:8],
                regs={0: 0}, setup=setup, check=check, label=label)


def backward_cases(rng):
    for _ in range(3):
        yield backward_case(rng, b"", "bottom=0", null=True)
    for size in range(0, 65):
        for style in ("run", "pattern", "text", "random"):
            yield backward_case(rng, sample_data(rng, size, style), "%s n=%d" % (style, size), rng.randrange(3))
    block = rng.randbytes(4098)
    yield backward_case(rng, block + block + block[:40], "distance 4098")
    yield backward_case(rng, rng.randbytes(4099) + block[:30] + rng.randbytes(4069) + block[:30], "distance 4099")
    for size in (0x1000, 0x2000, 0x6000):
        yield backward_case(rng, sample_data(rng, size, "text"), "text n=0x%x" % size)
        yield backward_case(rng, sample_data(rng, size, "run"), "run n=0x%x" % size)
    for _ in range(120):
        size = rng.choice((rng.randrange(65, 600), rng.randrange(600, 5000)))
        style = rng.choice(("pattern", "text", "text", "random"))
        data = sample_data(rng, size, style)
        if rng.random() < 0.3:
            data = rng.randbytes(rng.randrange(1, 200)) + data     # incompressible head
        yield backward_case(rng, data, "%s n=%d" % (style, size), rng.randrange(4))


ROUTINES = [
    Routine("CP_SaveContext", "libs/nitro/gx/asm_stubs/auto/CP_SaveContext.c", DOC, save_cases),
    Routine("CPi_RestoreContext", "libs/nitro/gx/asm_stubs/auto/CPi_RestoreContext.c", DOC, restore_cases),
    Routine("OS_GetLockID", "libs/nitro/os/asm_stubs/auto/OS_GetLockID.c", DOC, lock_cases),
    Routine("OSi_AlarmHandler", "libs/nitro/os/asm_stubs/calls/OSi_AlarmHandler.c", DOC,
            wrapper_cases(0x02004440, (0x02004450,))),
    Routine("OSi_GetAndDisplayContext", "libs/nitro/os/asm_stubs/calls/OSi_GetAndDisplayContext.c", DOC,
            wrapper_cases(0x02003DA8, (0x02003DBC, 0x02003E3C))),
    Routine("MIi_UncompressBackward", "libs/nitro/init/asm_stubs/auto/MIi_UncompressBackward.c", DOC, backward_cases),
    Routine("MI_ReadUncompLZ8", "libs/nitro/mi/asm_stubs/calls/MI_ReadUncompLZ8.c", DOC, lz_cases),
]
