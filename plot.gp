# HW1 plot
reset
set title '<title>'
set ylabel '<yLabel>'
set xlabel '<xLabel>'
set grid
set terminal postscript enhanced color font 'Ariel,10'
set output 'out.eps'
plot 'binary_ga.csv'