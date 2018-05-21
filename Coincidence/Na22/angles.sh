#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Na22_correlation.txt
touch Na22_correlation.txt
echo "Theta	N_counts errTheta errN_counts" > Na22_correlation.txt
echo -n "0" >> Na22_correlation.txt
cd deg00
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "5" >> Na22_correlation.txt
cd deg05
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "10" >> Na22_correlation.txt
cd deg10
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "15" >> Na22_correlation.txt
cd deg15
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "20" >> Na22_correlation.txt
cd deg20
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "25" >> Na22_correlation.txt
cd deg25
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "30" >> Na22_correlation.txt
cd deg30
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "45" >> Na22_correlation.txt
cd deg45
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "60" >> Na22_correlation.txt
cd deg60
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "75" >> Na22_correlation.txt
cd deg75
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "90" >> Na22_correlation.txt
cd deg90
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

cat Na22_correlation.txt
