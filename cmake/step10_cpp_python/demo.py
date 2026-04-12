"""
Step 10 demo: using a C++ library from Python via pybind11.

Run with:
    cmake --build build --target run_demo
Or manually:
    PYTHONPATH=build python3 demo.py
"""

import math
import time
import myvec3                          # the C++ extension module

print("=" * 52)
print("  Step 10: C++ library called from Python (pybind11)")
print("=" * 52)

# ── Vec3 class ────────────────────────────────────────────────────────────────
print("\n--- Vec3 class ---")
a = myvec3.Vec3(1.0, 2.0, 3.0)
b = myvec3.Vec3(4.0, 5.0, 6.0)

print(f"a            = {a}")
print(f"b            = {b}")
print(f"a + b        = {a + b}")
print(f"a - b        = {a - b}")
print(f"a * 2        = {a * 2}")
print(f"a.dot(b)     = {a.dot(b)}")
print(f"a.cross(b)   = {a.cross(b)}")
print(f"|a|          = {a.norm():.6f}")
print(f"|b|          = {b.norm():.6f}")
print(f"a normalised = {a.normalize()}")

angle_rad = a.angle_to(b)
print(f"angle(a,b)   = {angle_rad:.6f} rad  ({math.degrees(angle_rad):.4f}°)")

# Verify cross product property: a × b is perpendicular to both a and b
c = a.cross(b)
print(f"\nVerify cross product is perpendicular:")
print(f"  (a×b)·a = {c.dot(a):.10f}  (should be ~0)")
print(f"  (a×b)·b = {c.dot(b):.10f}  (should be ~0)")

# ── Stats submodule ───────────────────────────────────────────────────────────
print("\n--- Stats (C++ backend) ---")
data = [2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0]
print(f"data       = {data}")
print(f"mean       = {myvec3.stats.mean(data)}")
print(f"variance   = {myvec3.stats.variance(data)}")
print(f"stddev     = {myvec3.stats.stddev(data):.6f}")
print(f"median     = {myvec3.stats.median(data)}")

x = [1.0, 2.0, 3.0, 4.0, 5.0]
y = [2.1, 3.9, 6.2, 7.8, 10.1]
print(f"\ncorr(x, y) = {myvec3.stats.correlation(x, y):.6f}  (near 1 = strong positive)")

x2 = [1.0, 2.0, 3.0, 4.0, 5.0]
y2 = [5.0, 4.0, 3.0, 2.0, 1.0]
print(f"corr(x, -y)= {myvec3.stats.correlation(x2, y2):.6f}  (near -1 = strong negative)")

# ── Performance comparison: C++ vs pure Python ────────────────────────────────
# NOTE: for tiny operations (3-element dot product), Python object-call
# overhead can dominate. C++ shines when the work per call is larger.
# We compare computing stats.stddev on a 10 000-element list, 1 000 times.
print("\n--- Performance: C++ vs Python (stddev on 10k-element list × 1000 calls) ---")
import random
big_data = [random.gauss(0.0, 1.0) for _ in range(10_000)]
REPS = 1_000

# C++ stats.stddev (single C++ call per rep)
t0 = time.perf_counter()
for _ in range(REPS):
    myvec3.stats.stddev(big_data)
cpp_time = time.perf_counter() - t0

# Pure Python equivalent
def py_stddev(v):
    n = len(v)
    m = sum(v) / n
    return (sum((x - m)**2 for x in v) / n) ** 0.5

t0 = time.perf_counter()
for _ in range(REPS):
    py_stddev(big_data)
py_time = time.perf_counter() - t0

speedup = py_time / cpp_time
print(f"C++ stddev  : {cpp_time*1000:.1f} ms  ({REPS} calls × 10k elements)")
print(f"Python      : {py_time*1000:.1f} ms")
print(f"Speedup     : {speedup:.1f}x  ({'C++ is faster' if speedup > 1 else 'Python overhead dominates — try larger data or fewer calls'})")
print()
print("Lesson: pybind11 shines for compute-heavy work per call.")
print("        Fine-grained calls (millions of 3-element ops) are dominated")
print("        by Python<->C++ call overhead, not compute time.")

# ── Introspection: pybind11 module exposes Python-standard interfaces ─────────
print("\n--- Module introspection ---")
print(f"module name  : {myvec3.__name__}")
print(f"module doc   : {myvec3.__doc__}")
print(f"Vec3 doc     : {myvec3.Vec3.__doc__}")
print(f"help(norm)   : {myvec3.Vec3.norm.__doc__}")
