"""NitroSDK wireless helper (WH, the demos' wireless_shared library) in ov015: WH_StateInStartScan.

The routine is the SDK's C with one inline `clz` (MATH_CountLeadingZeros), which
no compiler of this project emits from C, so it is reported as verified library
code. The model is its contract: pick the channel to scan (the requested one, or
the next allowed channel after the one scanned last), fill the scan parameters and
start the scan. WM_GetAllowedChannel, GetDispersionScanPeriod and WM_StartScanEx
are replaced by THUMB stubs, WH_SetError by an ARM stub, all of which log their
arguments; MI_CpuFill8 runs from the ROM. Every case compares the return value,
the logged calls and the whole helper state and parameter block with the model.
"""

from arm_exec import Memory
from verify_sdklib import STACK_TOP, Case, Routine, load_symbols

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_wh.md"
MODULE = "ov015"
SYMBOLS = load_symbols()
UNCALLED = 0xDEADBEEF
LOG = 0x02390000                          # stub logs, away from SCRATCH and the stack


def bss(name: str) -> int:
    import re
    from verify_sdklib import EU
    text = (EU / "config" / "arm9" / "overlays" / MODULE / "symbols.txt").read_text(encoding="utf-8")
    return int(re.search(r"^%s kind:bss addr:0x([0-9a-f]+)" % name, text, re.M).group(1), 16)


STATE, PARAM, BUFFER = bss("gWhState"), bss("gWhScanExParam"), bss("gWirelessScanBuffer")
PARAM_SIZE, STATE_SIZE = 0x44, 0x10


def thumb_return(value: int) -> bytes:
    """ldr r0, [pc, #0]; bx lr; .word value"""
    return (0x4800).to_bytes(2, "little") + (0x4770).to_bytes(2, "little") + (value & MASK).to_bytes(4, "little")


def thumb_logger(log: int, result: int) -> bytes:
    """Store r0 and r1 at `log`, return `result`."""
    half = (0x4A02, 0x6010, 0x6051, 0x4802, 0x4770, 0x46C0)       # ldr r2,=log; str r0,[r2]; str r1,[r2,#4];
    return b"".join(h.to_bytes(2, "little") for h in half) + \
        log.to_bytes(4, "little") + (result & MASK).to_bytes(4, "little")   # ldr r0,=result; bx lr; nop


def arm_logger(log: int) -> bytes:
    """ldr r1, =log; str r0, [r1]; bx lr"""
    words = (0xE59F1004, 0xE5810000, 0xE12FFF1E, log)
    return b"".join(w.to_bytes(4, "little") for w in words)


def poke(mem: Memory, at: int, data: bytes) -> None:
    for i, value in enumerate(data):
        mem.write(at + i, 1, value)


def clz(value: int) -> int:
    return 32 - value.bit_length() if value else 32


def model(allowed: int, requested: int, channel_list: int, period: int, result: int):
    """(return value, error code or None, new channel list or None when no scan starts)."""
    if allowed == 0x8000:
        return 0, 3, None
    if allowed == 0:
        return 0, 0x16, None
    if requested == 0:
        channel = 32 - clz(~channel_list & (channel_list - 1) & MASK) + 1
        while True:
            channel += 1
            if channel > 16:
                channel = 1
            if allowed & (1 << (channel - 1)):
                break
        channel_list = (1 << (channel - 1)) & 0xFFFF
    else:
        channel_list = (1 << (requested - 1)) & 0xFFFF
    if result == 2:
        return 1, None, channel_list
    return 0, result, channel_list


def scan_cases(rng):
    allowed_stub = SYMBOLS["WM_GetAllowedChannel"][0]
    period_stub = SYMBOLS["GetDispersionScanPeriod"][0]
    start_stub = SYMBOLS["WM_StartScanEx"][0]
    error_stub = SYMBOLS["WH_SetError"][0]
    callback = SYMBOLS["WH_StateOutStartScanEx"][0]
    specials = [0, 0x8000, 0x8001, 0x0001, 0x7FFF, 0xFFFF, 0x4000]
    for k in range(300):
        allowed = specials[k] if k < len(specials) else rng.choice((rng.getrandbits(16), 1 << rng.randrange(16)))
        requested = 0 if rng.random() < 0.6 else rng.randint(1, 16)
        channel_list = rng.choice((0, 1 << rng.randrange(16), rng.getrandbits(16)))
        period = rng.getrandbits(16)
        result = rng.choice((2, 2, 0, 1, 3, 4, rng.getrandbits(8)))
        state = bytearray(rng.randbytes(STATE_SIZE))
        state[0xE:0x10] = requested.to_bytes(2, "little")
        param = bytearray(rng.randbytes(PARAM_SIZE))
        param[6:8] = channel_list.to_bytes(2, "little")
        ret, error, new_list = model(allowed, requested, channel_list, period, result)
        after = bytearray(param)
        if new_list is not None:
            after[0:4] = BUFFER.to_bytes(4, "little")
            after[4:6] = (0x400).to_bytes(2, "little")
            after[6:8] = new_list.to_bytes(2, "little")
            after[8:10] = period.to_bytes(2, "little")
            after[0x10:0x12] = (1).to_bytes(2, "little")
            after[0x12:0x14] = bytes(2)
            after[0x14:0x34] = b"\xff" * 32

        def setup(mem, state=state, param=param, allowed=allowed, period=period, result=result):
            poke(mem, allowed_stub, thumb_return(allowed))
            poke(mem, period_stub, thumb_return(period))
            poke(mem, start_stub, thumb_logger(LOG, result))
            poke(mem, error_stub, arm_logger(LOG + 8))
            poke(mem, LOG, b"".join(UNCALLED.to_bytes(4, "little") for _ in range(3)))
            poke(mem, STATE, state)
            poke(mem, PARAM, param)

        def check(cpu, state=state, after=after, error=error, new_list=new_list):
            mem = cpu.mem
            started = [mem.read(LOG, 4), mem.read(LOG + 4, 4)]
            want = [callback, PARAM] if new_list is not None else [UNCALLED, UNCALLED]
            if started != want:
                return "WM_StartScanEx log %s, model %s" % (["%08x" % w for w in started], ["%08x" % w for w in want])
            got_error = mem.read(LOG + 8, 4)
            if got_error != (UNCALLED if error is None else error & MASK):
                return "WH_SetError(%08x), model %s" % (got_error, error)
            if mem.bytes(PARAM, PARAM_SIZE) != bytes(after):
                got = mem.bytes(PARAM, PARAM_SIZE)
                bad = next(i for i in range(PARAM_SIZE) if got[i] != after[i])
                return "scan parameter byte +0x%x = 0x%02x, model 0x%02x" % (bad, got[bad], after[bad])
            if mem.bytes(STATE, STATE_SIZE) != bytes(state):
                return "helper state changed"
            for reg in range(4, 12):
                if cpu.r[reg] != 0:
                    return "r%d not preserved" % reg
            if cpu.r[13] != STACK_TOP:
                return "sp not restored"
            return None

        yield Case((), regs={0: ret}, setup=setup, check=check,
                   label="allowed=%04x requested=%d list=%04x result=%d" % (allowed, requested, channel_list, result))


ROUTINES = [
    Routine("WH_StateInStartScan", "src/overlays/ov015/calls/WH_StateInStartScan.c", DOC, scan_cases, module=MODULE),
]
