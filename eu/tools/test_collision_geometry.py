"""Check recovered geometry contracts against the original ARM instructions.

Requires the local ROM-derived function index, not a compiler or emulator app.
These checks do not change coverage or issue verified-library receipts.
"""
import itertools
import random
import struct
import sys
import unittest

from project import FUNC_INDEX, ROOT

sys.path.insert(0, str(ROOT.parent / "tools" / "mobiclip"))
from arm_exec import Cpu, Memory


class CollisionGeometryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest("extract the EU ROM and rebuild the function index first")
        import verify_idx
        cls.index = verify_idx._index()
        cls.addresses = verify_idx.SYM_ADDR

    def setUp(self):
        memory = Memory()
        for name in ("MakeSphereShape", "SphereToBounds", "Vec3AddScalar",
                     "Vec3SubScalar", "OffsetBoxByDelta"):
            memory.map(self.addresses[name], bytes.fromhex(self.index[name]["hex"]))
        memory.map(self.addresses["gCollisionBoundsDispatch"],
                   struct.pack("<6I", self.addresses["SphereToBounds"], 0, 0, 0, 0, 0))
        self.base = 0x01000000
        memory.map(self.base, size=0x10000)
        self.cpu = Cpu(memory)

    def write_vector(self, address, value):
        for i, word in enumerate(value):
            self.cpu.mem.write(address + 4 * i, 4, word)

    def read_words(self, address, count):
        return struct.unpack("<" + "i" * count, self.cpu.mem.bytes(address, count * 4))

    def call(self, name, *arguments):
        self.cpu.call(self.addresses[name], arguments, sp=self.base + 0xfff0, limit=1000)

    def test_sphere_constructor_and_bounds_order(self):
        rng = random.Random(0x0203ad28)
        centers = [(0, 0, 0), (-4096, 0, 4096)]
        centers += [tuple(rng.randint(-0x100000, 0x100000) for _ in range(3)) for _ in range(100)]
        shape, sphere, center = self.base, self.base + 0x40, self.base + 0x80
        for point, radius in itertools.product(centers, (0, 1, 0x200, 0x1000)):
            with self.subTest(center=point, radius=radius):
                self.write_vector(center, point)
                self.call("MakeSphereShape", shape, sphere, center, radius)
                self.assertEqual(self.cpu.mem.read(shape, 4), sphere)
                self.assertEqual(self.cpu.mem.read(shape + 0x1c, 4), 0)
                self.assertEqual(self.read_words(sphere, 4), point + (radius,))
                expected = tuple(x + radius for x in point) + tuple(x - radius for x in point)
                self.assertEqual(self.read_words(shape + 4, 6), expected)
                self.assertEqual(self.read_words(center, 3), point)

    def test_swept_bounds_signs_and_in_place_output(self):
        rng = random.Random(0x0203ac84)
        bounds = (4096, 8192, 12288, -4096, -8192, -12288)
        deltas = list(itertools.product((-0x200, 0, 0x200), repeat=3))
        deltas += [tuple(rng.randint(-0x8000, 0x8000) for _ in range(3)) for _ in range(200)]
        source, separate_out, delta_address = self.base + 0x40, self.base + 0x100, self.base + 0x200
        for delta, in_place in itertools.product(deltas, (False, True)):
            with self.subTest(delta=delta, in_place=in_place):
                self.write_vector(source, bounds)
                self.write_vector(delta_address, delta)
                out = source if in_place else separate_out
                self.cpu.mem.write(out - 4, 4, 0xa5a5a5a5)
                self.cpu.mem.write(out + 24, 4, 0xa5a5a5a5)
                self.call("OffsetBoxByDelta", source, out, delta_address)
                expected = tuple(bounds[i] + max(delta[i], 0) for i in range(3))
                expected += tuple(bounds[i + 3] + min(delta[i], 0) for i in range(3))
                self.assertEqual(self.read_words(out, 6), expected)
                self.assertEqual(self.read_words(delta_address, 3), delta)
                if not in_place:
                    self.assertEqual(self.read_words(source, 6), bounds)
                self.assertEqual(self.cpu.mem.read(out - 4, 4), 0xa5a5a5a5)
                self.assertEqual(self.cpu.mem.read(out + 24, 4), 0xa5a5a5a5)


if __name__ == "__main__":
    unittest.main()
