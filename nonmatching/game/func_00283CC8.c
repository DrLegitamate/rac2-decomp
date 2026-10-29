/* func_00283CC8 - 24 bytes, 28 places (the boot and every level), retail at
   0x00283cc8: cvt.w.s $f0,$f12 ; cvt.s.w $f0,$f0 ; swc1 $f0,0($a0) ;
   sub.s $f0,$f12,$f0 ; jr $ra ; nop. The store is to $a0 and the float
   argument is in $f12, so the prototype is (f32 *, f32).

   Current-master check of the retained cast form: 32 bytes, 0/28 (supersedes
   the older 36-byte measurement). It takes the conversion through a GPR and
   keeps the converted value in $f1 rather than $f0; it also schedules `swc1`
   into the `jr $ra` delay slot, while retail stores before subtraction and
   leaves the return delay slot empty. A current-rounding-mode conversion that
   remains in the FPU and the retail FPR allocation are unresolved. A 29 October
   2026 `__builtin_rintf(a1)` probe in the original translation unit compiled
   to 76 bytes, 0/28; it calls helpers, spills f20, and stores after the return
   subtraction, so it is farther from the 24-byte retail body. A 29 October
   write-then-read probe (`*a0 = (f32)(int)a1; return a1 - *a0;`) also remains
   32 bytes, 0/28. The compiler still sinks `swc1` into the `jr $ra` delay
   slot, retaining the GPR round trip and `$f1` allocation. */
typedef float f32;

f32 func_00283CC8(f32 *a0, f32 a1) { f32 b = (f32)(int)a1; *a0 = b; return a1 - b; }
