rm result.csv
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.9 -pm 0.1 -method whole -title rGA-whole
RGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.9 -pm 0.1 -method uni -title rGA-uniform
BGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.9 -pm 0.01 -method 2pt -title bGA-2pt
BGA -popu 100 -N 10 -len 10 -gen 500 -trial 30 -tnmt 2 -pc 0.9 -pm 0.01 -method uni -title bGA-uniform
python aoto_eps\transpose.py result.csv aoto_eps\out.csv eps\4GAs-P1000N100.eps
