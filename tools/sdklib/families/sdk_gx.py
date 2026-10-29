"""NitroSDK geometry FIFO bursts (GX_SendFifo48B).

The model is the routine's C-level contract: twelve source words, in order, as
four groups of three stored to dst, dst + 4 and dst + 8, which the geometry
FIFO's mirrored address range turns into one ordered stream.

Every case fills a 4 KB window at SCRATCH with random bytes and logs each store,
so a write to any other address, a missing or reordered word, or a change to the
source buffer is caught. r4-r11 and sp must come back unchanged.
"""

from arm_exec import Memory
from verify_sdklib import SCRATCH, STACK_TOP, Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_gx.md"
WINDOW = 0x1000
GXFIFO = 0x04000400          # geometry command FIFO, a write-only I/O port
BURST_WORDS = 12


# -- model ----------------------------------------------------------------------
def burst_writes(data: bytes, src: int, port: int) -> list:
    """The stores GX_SendFifo48B makes: word i goes to port + 4 * (i % 3)."""
    return [(port + 4 * (i % 3), 4, int.from_bytes(data[src + 4 * i:src + 4 * i + 4], "little"))
            for i in range(BURST_WORDS)]


# -- case plumbing --------------------------------------------------------------
def saved_registers(cpu) -> str | None:
    for reg in range(4, 12):
        if cpu.r[reg] != 0:
            return "r%d not preserved" % reg
    if cpu.r[13] != STACK_TOP:
        return "sp not restored"
    return None


def logged_case(data: bytes, src: int, port: int, label: str) -> Case:
    """Run with every store logged; the port must see exactly the model's writes."""
    expect = burst_writes(data, src - SCRATCH, port)
    after = bytearray(data)
    if SCRATCH <= port < SCRATCH + WINDOW:
        # A RAM destination keeps only the last group of three words.
        after[port - SCRATCH:port - SCRATCH + 12] = data[src - SCRATCH + 36:src - SCRATCH + 48]
    log = []

    def setup(mem: Memory) -> None:
        if not any(lo <= GXFIFO < hi for lo, hi, _ in mem.regions):
            mem.map(GXFIFO, size=12)
        mem.__dict__.pop("write", None)
        buf, off = mem._find(SCRATCH, WINDOW)
        buf[off:off + WINDOW] = data

        def logged(address, width, value):
            log.append((address, width, value & MASK))
            Memory.write(mem, address, width, value)
        mem.write = logged

    def check(cpu) -> str | None:
        cpu.mem.__dict__.pop("write", None)
        if log != expect:
            return "destination received %d writes, model %d words in order" % (len(log), len(expect))
        if cpu.mem.bytes(SCRATCH, WINDOW) != bytes(after):
            return "memory outside the destination changed"
        return saved_registers(cpu)

    return Case((src, port), regs={0: src + 4 * BURST_WORDS, 1: port},
                setup=setup, check=check, label=label)


def burst_cases(rng):
    """Port cases over the whole window, plus RAM destinations away from the source."""
    for _ in range(300):
        data = rng.randbytes(WINDOW)
        src = SCRATCH + 4 * rng.randrange((WINDOW - 4 * BURST_WORDS) // 4 + 1)
        yield logged_case(data, src, GXFIFO, "port src=+0x%x" % (src - SCRATCH))
    for _ in range(100):
        data = rng.randbytes(WINDOW)
        src = SCRATCH + 4 * rng.randrange(0x200 // 4)
        dst = SCRATCH + 0x400 + 4 * rng.randrange(0x200 // 4)
        yield logged_case(data, src, dst, "ram src=+0x%x dst=+0x%x" % (src - SCRATCH, dst - SCRATCH))


ROUTINES = [
    Routine("GX_SendFifo48B", "libs/nitro/gx/asm_stubs/auto/GX_SendFifo48B.c", DOC, burst_cases),
]
