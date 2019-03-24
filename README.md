# A simple flow solver 

developed in C++ and CUDA is under construction here.

The idea is to use expression templates for maximum performance and expressivness on the C++ side, while interfacing to CUDA for high performance solve.

The plan is to allow for switching between Eigen and hand rolled 
expressin templates on the C++ side, and between, ... thrust, cuBlas, etc., and hand rolled cuda on the GPU side.  By doing this I hope to increase my proficiency with all the components involved.

