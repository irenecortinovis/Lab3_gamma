#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Co60_correlation.txt
touch Co60_correlation.txt
echo "Theta	N_counts errTheta errN_counts" > Co60_correlation.txt
echo -n "0" >> Co60_correlation.txt
cd deg00
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "10" >> Co60_correlation.txt
cd deg10
../../../Code/easyfit.o histo.dat r Co60
cd ..

#echo -n "20" >> Co60_correlation.txt
#cd deg20
#../../../Code/easyfit.o histo.dat r Co60
#cd ..

#echo -n "30" >> Co60_correlation.txt
#cd deg30
#../../../Code/easyfit.o histo.dat r Co60
#cd ..

echo -n "90" >> Co60_correlation.txt
cd deg90
../../../Code/easyfit.o histo.dat r Co60
cd ..

cat Co60_correlation.txt