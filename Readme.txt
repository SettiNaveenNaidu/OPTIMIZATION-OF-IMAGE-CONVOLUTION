Serial.cpp = sequential execution of the program.
opemmp.cpp = Open MP method execution of the program.
cuda.ipynb = Cuda method execution of the program.
mpi.cpp = MPI method execution of the program.

ioput.cpp = input and output of the image.

Serial, openmp, cuda, mpi are progams that take 'image.txt' as input and does convolution and generates 'output.txt' files.
These txt files contain the pixel data of image.
'ioput' is a program that takes 'image' as input and produces the 'txt' files for above mentioned programs.
This program also takes 'output.txt' file as input and writes back to image. Thus convolved image generated.

____________________________________________________________________

Serial.cpp execution:
---------------------
Input : 
cmake  .
make  . 
./ioput image.jpg 0

Run program for convolution:
g++ serial.cpp
./a.out

Write to image:
./ioput image.jpg 1
______________________________________________________________________

Open MP execution:
-------------------
Input : 
cmake  .
make  . 
./ioput image.jpg 0

Run program for convolution:
g++ openmp.cpp -fopenmp -o openmp
./openmp

Write to image:
./ioput image.jpg 1

_______________________________________________________________________

MPI Execution:
--------------
Input : 
cmake  .
make  . 
./ioput image.jpg 0

Run program for convolution:
mpiCC mpi.cpp -o mpi
mpirun -np 3 ./mpi

Write to image:
./ioput image.jpg 1

_________________________________________________________________________

Cuda Execution:
---------------

Run all the cells in google colab.