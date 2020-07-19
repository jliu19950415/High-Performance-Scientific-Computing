1. What level of SIMD/vector support does the CPU your computer provide?

AVX, AVX2, SSE2, SSE3, SSSE3, SSE4A, SSE41, SSE42

2. What is the maximum operand size that your computer will support?

16 for 256 bits

3. How many double-precision floating point numbers can fit into one operand given the maximum operand size that your CPU will support?

64 doubles

4. What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").

2112.0000 mHz

5. Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

I expect L1 cache to be 256K, and L2 cache size to be 1MB. The corresponding bandwidths are about 600GB/s and 200GB/s. The cache sizes are quite close to the true capacity

6. What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?

The potential maximum compute performance of my laptop is about 36 Gflop/s. The L1, L2, and RAM bandwidths are 690 GB/s, 250 GB/s, 180 GB/s. The measurements are pretty close.

7. Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

The potential maximum number of floating point opreations is 12 per cycle. The expected maximum number of floating point operations would be 120.

8. Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

The best performing pairs I got from running the script is ikj. Looping j in inner loop actually is looping over rows for both matrices, meanwhile, memory in ikj accessed sequentially and this most efficient loop is put in the inner loop.

9. What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?

Both A and B(transposed) are accessed sequentially in the horizontal direction to be unit stride. This is definitely beneficial as the processor automatically prefetches data when memory is acessed sequentially.

10. Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

Since C(i,j) is inner loop invariant in ijk order with B transposed, thus take C(i,j) out of the inner loop to store in register could largely improve the performance. 

11. What optimization is applied in going from ``mult_2`` to ``mult_3``?

mult_2: hoisting and tiling 
mult_3: hoisting, tiling, blocking and inner-outer loop positioning

12. How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?

The maximum chieved perfromance I got from my versions of ''mult'' is 14.6 Gflop/s. It doesn't reach the maximum.




