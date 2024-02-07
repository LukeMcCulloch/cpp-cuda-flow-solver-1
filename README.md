# A tiny flow solver... 

...developed in C++ and CUDA is under construction here.

The idea is to use expression templates, with smart caching, for maximum performance and expressiveness on the C++ side, while interfacing to CUDA for high performance linear algebra.

Caveat:  As alluded to above expression templates (with smart caching) are great for element-wise expressions.  
However, for computations involving matrix iteration caching is often the better solution.  Caching of matmul is now implemented.
Element-wise operations remain lazy unless they are needed 
as part of matmul, at which time they are pre-computed and cached.

Incidentally, cache time seems like a great spot to implement  
solver (or matmul method in the basic case) selection.  Coming soon.

The plan is to allow for switching between fast numerical libraries such as Eigen, and hand rolled 
expression templates on the C++ side, and between, ... thrust, cuBlas, etc., and hand rolled CUDA on the GPU side.  By doing this I hope to increase my proficiency with all the components involved.


NOTE:  by making the make file simply compile all the code direclty, the link issue has been hidden.  To be fixed sometime when I don't have anything more fun to do.  (Everywhere I look, fun stuff sits, waiting to be worked on!)

GPU note:  if you, like me, are often developing on ancient Nvidia hardware, 
and the GPU ``crashes,'' reset it with the following:

check what is using your GPU memory with:

		sudo fuser -v /dev/nvidia*

Your output will look something like this:

                     USER        PID  ACCESS COMMAND
/dev/nvidia0:        root       1256  F...m  Xorg
                     username   2057  F...m  compiz
                     username   2759  F...m  chrome
                     username   2777  F...m  chrome
                     username   20450 F...m  python
                     username   867530 F.... code

Then kill the PID that you no longer need 
(it's probably called 'XXXX F...m code') with:

		sudo kill -9 PID


  Also

https://stackoverflow.com/questions/10871412/resetting-gpu-and-driver-after-cuda-error

nvidia-smi --gpu-reset
