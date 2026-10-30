"""DS Protect runtime in ov104: dispatch trampolines, table initializers and the decoders.

DS Protect keeps its checks encrypted until they run. Each guarded function has
a 36-byte trampoline followed by a context record (DSProtWrapperContext); the
trampoline jumps to the shared dispatcher, Encryptor_DecryptionWrapperFragment,
which decrypts the function, calls it, encrypts it again and returns its result.
The trampolines and the encryptor themselves are stored scrambled; at start-up
five static initializers pass their function tables to
Encryptor_DecodeFunctionTable, which unscrambles each range in place.

The models below are those contracts. The trampoline and initializer cases stop
at, or log at, the address they transfer to; the dispatcher's callees and the
guarded function are replaced by small ARM stubs that log their arguments, clobber
r1-r3 and ip, and return a chosen value; the decoder runs over random code ranges
in a 4 KB window at SCRATCH with the ROM's own Encryptor_CategorizeInstruction,
and the whole window and the cache-maintenance log are compared with the model.
"""

import re
from pathlib import Path

from arm_exec import Memory, RETURN_SENTINEL
from verify_sdklib import EU, SCRATCH, STACK_TOP, Case, Routine, load_symbols

MASK = 0xFFFFFFFF
DOC = "docs/library/dsprot.md"
MODULE = "ov104"
WINDOW = 0x1000
SYMBOLS = load_symbols()


def bss_base() -> int:
    text = (EU / "config" / "arm9" / "overlays" / MODULE / "symbols.txt").read_text(encoding="utf-8")
    return int(re.search(r"^DSProt_BSS kind:bss addr:0x([0-9a-f]+)", text, re.M).group(1), 16)


DSPROT_BSS = bss_base()


def address(symbol: str) -> int:
    return SYMBOLS[symbol][0]


# -- tiny ARM stubs ----------------------------------------------------------------
def log_stub(registers, result=None):
    """Store each register to a log after the code, optionally load r0 = result, clobber, bx lr.

    Returns (code bytes, offset of the log). r0 is clobbered with `result` (or left),
    r1-r3 and ip get distinct marker values so that callers relying on them show up."""
    count = len(registers) + (result is not None) + 4 + 1
    log = 4 * count
    words = []
    for i, reg in enumerate(registers):
        words.append(0xE58F0000 | reg << 12 | (log + 4 * i - (4 * len(words) + 8)))   # str reg, [pc, #]
    if result is not None:
        literal = log + 4 * len(registers)
        words.append(0xE59F0000 | (literal - (4 * len(words) + 8)))                 # ldr r0, [pc, #]
    for reg, marker in ((1, 0xA1), (2, 0xA2), (3, 0xA3), (12, 0xAC)):
        words.append(0xE3A00000 | reg << 12 | marker)                                 # mov reg, #marker
    words.append(0xE12FFF1E)                                                          # bx lr
    words += [0] * len(registers)
    if result is not None:
        words.append(result & MASK)
    return b"".join(w.to_bytes(4, "little") for w in words), log


def poke(mem: Memory, at: int, data: bytes) -> None:
    for i in range(0, len(data), 4):
        mem.write(at + i, 4, int.from_bytes(data[i:i + 4], "little"))


def words(mem: Memory, at: int, count: int) -> list:
    return [mem.read(at + 4 * i, 4) for i in range(count)]


def saved_registers(cpu, skip=()) -> str | None:
    for reg in range(4, 12):
        if reg not in skip and cpu.r[reg] != 0:
            return "r%d not preserved" % reg
    if cpu.r[13] != STACK_TOP:
        return "sp not restored"
    return None


# -- trampolines -------------------------------------------------------------------
def trampoline_cases(symbol: str):
    """Jump to (context word +0x14) - 0x1000 with ip = context, everything else untouched."""
    entry = address(symbol)
    context = entry + 0x24

    def cases(rng):
        for k in range(150):
            target = SCRATCH + 4 * rng.randrange((WINDOW - 0x40) // 4)
            args = tuple(rng.getrandbits(32) for _ in range(4))
            stub, log = log_stub((0, 1, 2, 3, 12, 13, 14))

            def setup(mem, target=target, stub=stub):
                poke(mem, context + 0x14, ((target + 0x1000) & MASK).to_bytes(4, "little"))
                poke(mem, target, stub)

            def check(cpu, target=target, log=log, args=args):
                got = words(cpu.mem, target + log, 7)
                want = list(args) + [context, STACK_TOP, RETURN_SENTINEL]
                if got != want:
                    return "target saw %s, model %s" % (["%08x" % w for w in got], ["%08x" % w for w in want])
                return saved_registers(cpu)

            yield Case(args, setup=setup, check=check, label="target=0x%x" % target)
    return cases


# -- static initializers -----------------------------------------------------------
def initializer_cases(symbol: str):
    """Tail-call Encryptor_DecodeFunctionTable(entry + 12): the table right after the code."""
    entry = address(symbol)
    decoder = address("Encryptor_DecodeFunctionTable")

    def cases(rng):
        stub, log = log_stub((0, 1, 2, 3, 13, 14))
        for k in range(120):
            args = tuple(rng.getrandbits(32) for _ in range(4))

            def setup(mem, stub=stub):
                poke(mem, decoder, stub)

            def check(cpu, log=log, args=args):
                got = words(cpu.mem, decoder + log, 6)
                want = [entry + 12] + list(args[1:]) + [STACK_TOP, RETURN_SENTINEL]
                if got != want:
                    return "decoder saw %s, model %s" % (["%08x" % w for w in got], ["%08x" % w for w in want])
                return saved_registers(cpu)

            yield Case(args, setup=setup, check=check, label="r1-r3 random")
    return cases


# -- dispatcher --------------------------------------------------------------------
def dispatcher_cases(rng):
    """Decrypt, call, re-encrypt; context: return address, key, function info, saved r10."""
    decrypt, encrypt = address("Encryptor_DecryptFunction"), address("Encryptor_EncryptFunction")
    for k in range(150):
        context = SCRATCH + 4 * rng.randrange(0x40)
        function = SCRATCH + 0x400 + 4 * rng.randrange(0x40)
        key, info_address, info_size = (rng.getrandbits(32) for _ in range(3))
        result, new_key, r10 = (rng.getrandbits(32) for _ in range(3))
        args = [rng.getrandbits(32) for _ in range(4)]
        before = [rng.getrandbits(32), key, info_address, info_size, rng.getrandbits(32), rng.getrandbits(32)]
        f_stub, f_log = log_stub((0, 1, 2, 3, 10, 13), result)
        d_stub, d_log = log_stub((0, 1, 2, 10, 13), function)
        e_stub, e_log = log_stub((0, 1, 2, 10, 13), new_key)

        def setup(mem, context=context, before=before, function=function, f_stub=f_stub, d_stub=d_stub,
                  e_stub=e_stub):
            poke(mem, context, b"".join(w.to_bytes(4, "little") for w in before))
            poke(mem, function, f_stub)
            poke(mem, decrypt, d_stub)
            poke(mem, encrypt, e_stub)

        def check(cpu, context=context, before=before, function=function, f_log=f_log, d_log=d_log,
                  e_log=e_log, args=args, result=result, new_key=new_key, r10=r10):
            frame = STACK_TOP - 0x10                  # r0-r3 pushed while the function is decrypted
            want = {
                "decrypt": ([key, info_address, info_size, context, frame], words(cpu.mem, decrypt + d_log, 5)),
                "function": (args + [context, STACK_TOP], words(cpu.mem, function + f_log, 6)),
                "encrypt": ([key, info_address, info_size, context, STACK_TOP - 4], words(cpu.mem, encrypt + e_log, 5)),
                "context": ([STACK_TOP, new_key, info_address, info_size, r10, before[5]], words(cpu.mem, context, 6)),
            }
            for name, (model, got) in want.items():
                if got != [w & MASK for w in model]:
                    return "%s %s, model %s" % (name, ["%08x" % w for w in got], ["%08x" % (w & MASK) for w in model])
            if cpu.r[10] != r10:
                return "r10 not restored"
            return saved_registers(cpu, skip=(10,))

        regs = args + [0] * 6 + [r10, 0, context]
        yield Case(tuple(regs), regs={0: result}, setup=setup, check=check, label="context=0x%x" % context)


# -- table decoder -----------------------------------------------------------------
def categorize(word: int) -> int:
    """Encryptor_CategorizeInstruction: 1 = BLX imm, 2 = BL, 3 = B, 0 = anything else."""
    top = word >> 24
    if top & 0xE == 0xA:
        if top & 0xF0 == 0xF0:
            return 1
        return 2 if top & 1 else 3
    return 0


def decode_range(window: bytearray, offset: int, count: int) -> None:
    key = 0xF0B9A2EA
    for i in range(count):
        at = offset + 4 * i
        word = int.from_bytes(window[at:at + 4], "little")
        kind = categorize(word)
        if kind in (1, 3):
            word = ((word & 0xFF000000) ^ 0x01000000) | (((word & 0xFFFFFF) - 0x402) & 0xFFFFFF)
            key = (key ^ (word >> 24)) & 0xFFFFFF
        else:
            if kind == 2:
                word ^= 0x01000000
            word ^= key
            key = (key ^ word ^ (word >> 8)) & 0xFFFFFF
        window[at:at + 4] = word.to_bytes(4, "little")


def cache_log() -> list:
    """Clean+invalidate every D-cache line by set/index, then invalidate the I-cache."""
    log = []
    for way in (0, 0x40000000, 0x80000000, 0xC0000000):
        for line in range(0, 0x400, 0x20):
            log += [(10, 4, 0), (14, 2, way | line)]
    return log + [(5, 0, 0), (10, 4, 0)]


def code_word(rng) -> int:
    choice = rng.random()
    if choice < 0.15:
        return rng.choice((0xEA, 0xEB, 0xFA, 0xFB, 0x0A, 0x1B, 0xDA)) << 24 | rng.getrandbits(24)
    return rng.getrandbits(32)


def decoder_cases(rng):
    for k in range(120):
        window = bytearray(rng.randbytes(WINDOW))
        for i in range(0, WINDOW, 4):
            window[i:i + 4] = code_word(rng).to_bytes(4, "little")
        functions = rng.randint(1, 4)
        table = 0xC + 4 * rng.randrange(8)                  # three words before the table are cleared
        ranges, cursor = [], 0x100
        for f in range(functions):
            count = rng.randint(0, 48)
            ranges.append((cursor, count))
            cursor += 4 * count + 4 * rng.randrange(4)
        after = bytearray(window)
        for i in range(3):
            after[table - 12 + 4 * i:table - 8 + 4 * i] = bytes(4)
        for f, (offset, count) in enumerate(ranges):
            entry = table + 8 * f
            spare = rng.randrange(4)                        # size bits below a whole word are ignored
            encoded = ((SCRATCH + offset + 0x1000) & MASK, (DSPROT_BSS + 0x1000 + 4 * count + spare) & MASK)
            for j, value in enumerate(encoded):
                window[entry + 4 * j:entry + 4 * j + 4] = value.to_bytes(4, "little")
            decode_range(after, offset, count)
            after[entry:entry + 8] = bytes(8)
        end = table + 8 * functions
        window[end:end + 4] = bytes(4)                      # terminator: an address of zero
        after[end:end + 4] = bytes(4)
        cache = cache_log() * functions

        def setup(mem, window=window):
            buf, off = mem._find(SCRATCH, WINDOW)
            buf[off:off + WINDOW] = window

        def check(cpu, after=after, cache=cache):
            got = cpu.mem.bytes(SCRATCH, WINDOW)
            log, cpu.cp15_log[:] = list(cpu.cp15_log), []
            if got != bytes(after):
                bad = next(i for i in range(WINDOW) if got[i] != after[i])
                return "byte at +0x%x = 0x%02x, model 0x%02x" % (bad, got[bad], after[bad])
            if log != cache:
                return "cache maintenance differs (%d operations, model %d)" % (len(log), len(cache))
            return saved_registers(cpu)

        yield Case((SCRATCH + table,), setup=setup, check=check,
                   label="%d ranges, %s words" % (functions, [c for _, c in ranges]))


TRAMPOLINES = [
    "__DSProt_DetectFlashcart", "__DSProt_DetectNotFlashcart", "__DSProt_DetectEmulator",
    "__DSProt_DetectNotEmulator", "__DSProt_DetectDummy", "__DSProt_DetectNotDummy",
    "RunEncrypted_Integrity_MACOwner_IsBad", "RunEncrypted_Integrity_MACOwner_IsGood",
    "RunEncrypted_Integrity_ROMTest_IsBad", "RunEncrypted_Integrity_ROMTest_IsGood",
    "RunEncrypted_MACOwner_IsBad", "RunEncrypted_MACOwner_IsGood", "RunEncrypted_ROMUtil_CRC32",
    "RunEncrypted_ROMTest_IsBad", "RunEncrypted_ROMTest_IsGood", "RunEncrypted_Dummy_IsBad",
    "RunEncrypted_Dummy_IsGood",
]
INITIALIZERS = ["__sinit_ov104_020d2028", "__sinit_ov104_020d25d0", "__sinit_ov104_020d2958",
                "__sinit_ov104_020d31fc", "__sinit_ov104_020d36b4"]
STUBS = "src/overlays/ov104/asm_stubs/calls/%s.c"

ROUTINES = (
    [Routine(name, STUBS % name, DOC, trampoline_cases(name), module=MODULE) for name in TRAMPOLINES]
    + [Routine(name, STUBS % name, DOC, initializer_cases(name), module=MODULE, object_gate=True)
       for name in INITIALIZERS]
    + [Routine("Encryptor_DecryptionWrapperFragment", "src/overlays/ov104/calls/Encryptor_DecryptionWrapperFragment.c",
               DOC, dispatcher_cases, module=MODULE, object_gate=True),
       Routine("Encryptor_DecodeFunctionTable", "src/overlays/ov104/calls/Encryptor_DecodeFunctionTable.c",
               DOC, decoder_cases, module=MODULE)]
)
