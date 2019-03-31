# A simple flow solver... 

...developed in C++ and CUDA is under construction here.

The idea is to use expression templates for maximum performance and expressivness on the C++ side, while interfacing to CUDA for high performance linear algebra.

The plan is to allow for switching between fast numerical libraries such as Eigen, and hand rolled 
expression templates on the C++ side, and between, ... thrust, cuBlas, etc., and hand rolled CUDA on the GPU side.  By doing this I hope to increase my proficiency with all the components involved.

