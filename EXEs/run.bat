rm resultP1000.csv
RGA -popu 1000 -N 100 -len 10 -gen 10000 -trial 30 -tnmt 2 -pc 0.9 -pm 0.1 -method whole -o resultP1000.csv -title rGA-whole
RGA -popu 1000 -N 100 -len 10 -gen 10000 -trial 30 -tnmt 2 -pc 0.9 -pm 0.1 -method uni -o resultP1000.csv -title rGA-uniform
BGA -popu 1000 -N 100 -len 10 -gen 10000 -trial 30 -tnmt 2 -pc 0.9 -pm 0.01 -method 2pt -o resultP1000.csv -title bGA-2pt
BGA -popu 1000 -N 100 -len 10 -gen 10000 -trial 30 -tnmt 2 -pc 0.9 -pm 0.01 -method uni -o resultP1000.csv -title bGA-uniform
python aoto_eps\transpose.py resultP1000.csv aoto_eps\out.csv eps\4GAs-P1000N100G10000.eps
