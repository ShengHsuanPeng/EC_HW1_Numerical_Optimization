filename = 'aoto_eps\out.csv'
outname = 'eps\4GAs-P1000N100.eps'
columns = 4


set style data linespoints
set nogrid
#set format x "%.0s"

set datafile separator ", "
set term postscript eps 21 enhanced color solid font ",24"
#============================================================================
set autoscale
#set logscale y
#set format y "10^{%L}"
set output outname

set ylabel "f(x)"
set xlabel "generations"
#set xrange [:]
set yrange [:]
set colorsequence classic

set pointsize 1

set key right top

set key autotitle columnhead
#plot "out.csv"     u 0:1  with lp pn 10 lt 1 pt 0 t  "Rg(N_P100,R2,F20)"
plot for [i=1:columns] filename  u 0:i  with lp pn 10 pt 0 #title columnhead

reset 
set output