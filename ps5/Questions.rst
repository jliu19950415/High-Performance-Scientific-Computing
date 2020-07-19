
pnorm
-----

* What was the data race?
Two thread access shared variable 'sum' at the same time, and tries modify it.

* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).
I added a local variable to the function worker_a, and use lock & guard technique when updating the sum.

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
1 thread < Sequential < 8 threads < 2 threads < 4 threads. In average, the parallelization version outperformed (speedup ~= 1.4) Sequential version 
when problem size  is small (1M-4M), the parallel speedup drops to around 1.15 as problem size grows to 32M

fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?
1 thread < Sequential. 2 threads: 1.16, 4 threads: 1.29, 8 threads: 1.34

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?
Overall, partitioned_two_norm_b has the same Gflops/s as the Sequential.  

* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.
Partitioned_two_norm_a doesn't improve the performance in average.


cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
From my tests, cyclic partitioning performed worse than Sequential regardless of number of threads.

* How does the performance of cyclic partitioning compare to blocked?  Explain any significant differences, referring to, say, performance models or CPU architectural models.
Cyclic partitioning is way slower than blocked partitioning. I guess the reason is that accessing memory sequentially is the most obvious advantage that blocked partitioning has over the cyclic partitioning.

rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
Overall, "async" version is slower than Sequential while "deferred" version has similar performance to Sequential, and the speedup is approximately 1.

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.
The function will be called at the point we revise the shared norm. In this case, ``std:::launch::deferred`` performed way better than ``std:::launch::async``

General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?
In general, blocked partitioning has very significant improvement in terms of speedup, while other implementations doesn't perform well comparing to Sequential model.

* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)
As indicated, the roofline model we used to calculate the maxima last several assignment suggest the upper bound of the computation speed thus the possible speedup.

Conundrum #1
------------

1. What is causing this behavior?
Thread are solving small problems, and these threads take time to create and thus take extra memory space and cache. The shared variable is locked so often that the spawning time costs too much.

2. How could this behavior be fixed?
Parallelizing in bigger chunks.


3. Is there a simple implementation for this fix?



Parallel matvec
---------------

* Which methods did you implement?
I used thread.

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?
On average, the speedup is around 1.5.


Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?
Transform CSR to CSC to achieve better t_mult performance or directly read the matrix in transposed form.

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?
Instead of read_csrmatrix we use read_cscmatrix which should be quite straightforward.

3. How would we use the second?
We could creat a read_t_csrmatrix function to read the transposed form.