::rm result.csv
g++ *.cpp -O2 -o BGA.exe
BGA -popu 100 -N 10 -len 10 -gen 500 -trial 100 -tnmt 2 -pc 0.0 -pm 0.01 -method 2pt 
::python aoto_eps\transpose.py result.csv aoto_eps\out.csv eps\test.eps
