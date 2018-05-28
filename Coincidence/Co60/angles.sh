#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Co60_correlation.txt
touch Co60_correlation.txt
echo "Theta	peak1	peak2" > Co60_correlation.txt
echo -n "0" >> Co60_correlation.txt
cd deg0_retake
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "10" >> Co60_correlation.txt
cd deg10
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "20" >> Co60_correlation.txt
cd deg20
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "30" >> Co60_correlation.txt
cd deg30
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "40" >> Co60_correlation.txt
cd deg40
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "50" >> Co60_correlation.txt
cd deg50
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "60" >> Co60_correlation.txt
cd deg60
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "70" >> Co60_correlation.txt
cd deg70
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "80" >> Co60_correlation.txt
cd deg80
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "90" >> Co60_correlation.txt
cd deg90
../../../Code/easyfit.o histo.dat r Co60
cd ..

cd HPGe_alone
../../../Code/easyfit.o histo.dat r Co60ratio
cd ..

cat Co60_correlation.txt
echo "ratio = $(cat ratio.txt)"
./correlation.o
