Admixture Model Simulator
==========
Admixture Model Described in Wenfei et al, Implemented in C++

Test

1)Run simulator
./AdmixModel -l 2.74 -e 5000 -n 100 -m 1 -p 0.5 -g 100 >hi_sim_100_50.txt

2)Fit results

Rscript fit.r hi_sim_100_50

Test Report

HI Model, Ne 5000, proportion 0.2, length 2.7 Morgan

g=10, 1.07s
g=20, 3.22s
g=50, 15.34s
g=100, 54.50s

GA Model, Ne 5000, proportion 0.2, length 2.7 Morgan

g=10, 0.96s
g=20, 3.07s
g=50, 15.00s
g=100, 51.99s

CGF Model, Ne 5000, proportion 0.2, length 2.7 Morgan

g=10, 0.90s
g=20, 2.79s
g=50, 13.37s
g=100, 46.16s
