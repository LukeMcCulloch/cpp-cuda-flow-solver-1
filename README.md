# A tiny flow solver... 

...developed in C++ and CUDA is under construction here.

The idea is to use expression templates, with smart caching, for maximum performance and expressiveness on the C++ side, while interfacing to CUDA for high performance linear algebra.

Caveat:  As alluded to above (smart caching) expression templates are great for element-wise expressions.  
However, for computations involving matrix iteration caching is often the better solution.  Caching of matmul is now implemented.
Element-wise operations remain lazy unless they are needed 
as part of matmul, at which time they are pre-computed and cached.

Incidentally, cache time seems like a great spot to implement  
solver (or matmul method in the basic case) selection.  Coming soon.

The plan is to allow for switching between fast numerical libraries such as Eigen, and hand rolled 
expression templates on the C++ side, and between, ... thrust, cuBlas, etc., and hand rolled CUDA on the GPU side.  By doing this I hope to increase my proficiency with all the components involved.


NOTE:  since switching to nvcc, this code has suddenly become invalid for Windows.  I will see if I can fix this if I have any time to look at it this week.