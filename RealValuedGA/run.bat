rm result.csv
g++ *.cpp -O2 -o RGA.exe
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 1.0 -pm 0.01 -method uni
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.9 -pm 0.01 -method uni
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.5 -pm 0.01 -method uni
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.1 -pm 0.01 -method uni
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.0 -pm 0.01 -method uni  
python aoto_eps\transpose.py result.csv aoto_eps\out.csv eps\change_pc_uni.eps
