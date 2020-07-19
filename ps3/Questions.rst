
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?

The name of the executable program

2. Which entry of `argv` holds the first argument passed to the program?

argv[1]

3. Which entry of `argv` holds the second argument passed to the program?

argv[2]

4. How would you print just the last argument passed to a program?

std::cout << argv[argc - 1] << std::endl;

float vs double
----------------

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.

On average, construction for double precision took 1.69 times longer to construct, as double requires more spaces to be allocated.

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.

About the same speed, which verifies that double precision floating-point operations may not be slower than single precision floats
on modern 64-bit machines.

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.

On average, construction for double precision took 2 times longer after o3 optimization. Same reason as 5.

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain. 

On average, the double took about 2 times longer to do multiplication with optimizaiton. It is a butterfly effect referring back
to class. When no optimization method was used, the significands are multiplied and the exponets are added, which involves a 
lot of memory accessing, addition and multiplication. After optimization, CPU load data from main memory into processor cache,
fetch a block of memory containing the requested data and adjacent data, which largely reduce the amount of time on memory accessing.
Since single precision has less memory to read, it has larger marginal gain than double precision.

9.  What is the difference (ratio) in execution times 
for double precision    multiplication with and without optimization? Explain. 

On average, multiplication after optimization is about 3.5 times faster than that without optimizaiton. Some optimization techniques
such as loop unrolling and pipelining are carried out by -o3 flag. Meanwhile, I believe caching is involved which allows data accessing 
is faster, while FLOP per cycle drops by optimization techniques as well.


Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?

Take mult0 as an example, there are four memory operations and two floating point operations per iteration. So total 6*(N^3) operations.
After doubling the problem size, the number of operations goes up to 6*(2N)^3. Thus O(N^3).

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?

Approximately 2^3 = 8 times.

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.

Mine was around 10X when calling mult_0. Memory fetching took a huge amount of time.

13.  What raio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?

About 8.4X. Hoisting and Tiling and Blocking are used for improving locality. Work with blocks that fit into cache for quick accessing.

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.
mult_1: About 10X.
mult_2: 8X ~ 10X.


All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?

As the matrix size grows and more optimizations are applied, the performance seems to follow diminishing marginal utility. While simple multiplication approach
didn't have such drop, matrix-transpose product performance drop after blocking is introduced. Tiling seems to be the most effective algorithm among all the 
optimizations. It costs performance to make transpose of A, and there is insignificant difference between a copy of A vs just passing in A itself. The performance
of passing A twice is about the same comparing to passing once.

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?
m_t_2(A,A) has performance of 6.99 Gflop/s. From my observation based on the table, when images data grows 10 times bigger, the performance drops about 1.5Gflop/s.
While doubling image size increase the cache used for blocking, even though it's not cubic, my guess would be something like n^2*long(n) that's between quadratic and cubic.


About PS3
---------


17. The most important thing I learned from this assignment was ...

Locality, Locality, Locality.

18. One thing I am still not clear on is ...

I'm not sure how to approaches all-pairs problem mathematically.
