#!/bin/sh
#Script per calcolare ( N(90°)-N(0°) ) / N(90°)
#Viene creato il file Na22_correlation.txt
touch Co60_test.txt
cd 10min_deg0_12cm
../../../Code/easyfit.o histo.dat r co60
cd ..

cd 10min_deg90_12cm
../../../Code/easyfit.o histo.dat r co60
cd ..

root -l diff.C
