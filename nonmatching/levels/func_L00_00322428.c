/* Batch 3 (2026-10-28) handoff notes:
Matched 27/27 only with per-use ref_L00_00322428_NN names (rejected as steering). Body, statement order (store of D_..7B90 first in the zero arm) and decls `float X MACRO_ADDR` are right: -O2 -G8 -ffunction-sections -frac2-keep-block-order, one D_001A.. name per variable and -G8 MACRO_ADDR gives the exact bytes in level 0.
Honest retry with D_001A790C-style names (one per variable): fails the link check "D_001A790C needs two values" in the other levels (their references resolve to different addresses than level 0), so a shared-function name for these needs a catalogue decision, not C.
*/

#include "common.h"

extern float ref_L00_00322428_00 MACRO_ADDR;
extern float ref_L00_00322428_01 MACRO_ADDR;
extern float ref_L00_00322428_02 MACRO_ADDR;
extern int ref_L00_00322428_03 MACRO_ADDR;
extern float ref_L00_00322428_04 MACRO_ADDR;
extern int ref_L00_00322428_05 MACRO_ADDR;
extern float ref_L00_00322428_06 MACRO_ADDR;
extern float ref_L00_00322428_07 MACRO_ADDR;
extern float ref_L00_00322428_08 MACRO_ADDR;
extern int ref_L00_00322428_09 MACRO_ADDR;
extern float ref_L00_00322428_10 MACRO_ADDR;
extern float ref_L00_00322428_11 MACRO_ADDR;
extern float ref_L00_00322428_12 MACRO_ADDR;
extern float ref_L00_00322428_13 MACRO_ADDR;
extern float ref_L00_00322428_14 MACRO_ADDR;
extern float ref_L00_00322428_15 MACRO_ADDR;
extern int ref_L00_00322428_16 MACRO_ADDR;
extern float ref_L00_00322428_17 MACRO_ADDR;

void func_L00_00322428(int mode) {
 if(mode==0) {
  float one = 1.0f;
  float frame = 1.0f/60.0f;
  float square = 1.0f/3600.0f;
  float cube = 1.0f/216000.0f;
  ref_L00_00322428_05=0;
  ref_L00_00322428_00=one;
  ref_L00_00322428_06=one;
  ref_L00_00322428_07=one;
  ref_L00_00322428_01=square;
  ref_L00_00322428_02=cube;
  ref_L00_00322428_03=5;
  ref_L00_00322428_04=frame;
  ref_L00_00322428_08=frame;
 } else {
  ref_L00_00322428_09=1;
  ref_L00_00322428_10=1.2f;
  ref_L00_00322428_11=1.44f;
  ref_L00_00322428_12=0.83333337306976318359375f;
  ref_L00_00322428_13=0.02000000141561031341552734375f;
  ref_L00_00322428_14=0.00040000001899898052215576171875f;
  ref_L00_00322428_15=0.000008f;
  ref_L00_00322428_16=6;
  ref_L00_00322428_17=0.02f;
 }
}
