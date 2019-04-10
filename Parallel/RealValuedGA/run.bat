g++ *.cpp -O2 -o RGA.exe
RGA -popu 100 -N 100 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 1.0 -pm 0.01 -method uni 
g++ *.cpp -O2 -o RGA.exe -fopenmp
RGA -popu 100 -N 100 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 1.0 -pm 0.01 -method uni 
