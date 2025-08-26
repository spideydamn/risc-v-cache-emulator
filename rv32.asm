addi    ra, zero, 164       // ra = 164                         (return instruction number)
addi   	s0, zero, 64        // M = 64                                                                   #define M 64
addi   	s1, zero, 60        // N = 60                                                                   #define N 60
addi   	s2, zero, 32        // K = 32                                                                   #define K 32
addi   	a0, zero, 0x100     // *pa = a                          (a0 == pa)                              int8_t *pa = a;
mul     t0, s0, s2          // t0 = M * K = 64 * 32 = 2048      (a.size(), size of a in bytes)
add   	a2, a0, t0          // b = 256 + 2048 = 2304            (a2 = a0 + t0 = 0x100 + M * K)
mul     t1, s1, s2          // t1 = N * K = 60 * 32 = 1920      (size of b in units)
add     t1, t1, t1          // t1 = N * K * 2 = 3840            (size of b in bytes)
add   	a3, a2, t1          // *pc = c                          (a3 = a2 + N * K * 2 == pc)             int32_t *pc = c;
addi    t1, zero, 0         // y = 0                            (t1 == y)                               for (int y = 0; y < M; y++) {
addi    t2, zero, 0         // x = 0                            (t2 == x)                               for (int x = 0; x < N; x++) {
add     a1, zero, a2        // *pb = b                          (a1 = a2 == pb)                         int16_t *pb = b;
addi    t4, zero, 0         // s = 0                            (t4 == s)                               int32_t s = 0;
addi    t3, zero, 0         // k = 0                            (t3 == k)                               for (int k = 0; k < K; k++) {
add     t5, a0, t3          // t5 = pa + k                      (place of pa[k])
add     t6, a1, t2          // t6 = pb + x
add     t6, t6, t2          // t6 = pb + 2 * x                  (place of pb[x])
lb      t5, 0, t5           // pa[k]                            (t5 = value on pa[k])
lh      t6, 0, t6           // pb[x]                            (t6 = value on pb[x])
mul     t5, t5, t6          // pa[k] * pb[x]                    (t5 = t5 * t6)
add     t4, t4, t5          // s += pa[k] * pb[x]               (t4 = t4 + t3)                          s += pa[k] * pb[x];
add     a1, a1, s1          // pb += N                          
add     a1, a1, s1          // pb += N * 2                      (+= size of N units of b in bytes)      pb += N;
addi    t3, t3, 1           // ++k
blt     t3, s2, -40         // while k < K                                                              }
add     t5, a3, t2          // t5 = pc + x
add     t5, t5, t2          // t5 = pc + 2 * x
add     t5, t5, t2          // t5 = pc + 3 * x
add     t5, t5, t2          // t5 = pc + 4 * x
sw      t4, 0, t5           // pc + x * 4 = s                                                           pc[x] = s;
addi    t2, t2, 1           // ++x
blt     t2, s1, -80         // while x < N                                                              }
add     a0, a0, s2          // pa += K                                                                  pa += K;
add     a3, a3, s1          // pc += N
add     a3, a3, s1          // pc += N * 2
add     a3, a3, s1          // pc += N * 3
add     a3, a3, s1          // pc += N * 4                      (+= size of N units of c in bytes)      pc += N;
addi    t1, t1, 1           // ++y
blt     t1, s0, -112        // while y < M                                                              }
jalr    zero, ra, 0         // return to ra