rm binary_ga.csv
REM g++ *.cpp -O2 -o BGA.exe
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 01 -N 10 -pc 0.9 -pm 0.01
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 02 -N 10 -pc 0.9 -pm 0.01
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 04 -N 10 -pc 0.9 -pm 0.01
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 08 -N 10 -pc 0.9 -pm 0.01
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 16 -N 10 -pc 0.9 -pm 0.01
BGA -popu 100 -len 10 -gen 500 -trial 30 -tnmt 32 -N 10 -pc 0.9 -pm 0.01
python aoto_eps\transpose.py binary_ga.csv aoto_eps\out.csv eps\change_n.eps
