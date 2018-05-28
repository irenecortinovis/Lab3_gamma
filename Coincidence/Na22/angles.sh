#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Na22_correlation.txt
touch Na22_correlation.txt
echo "Theta	N_counts errTheta errN_counts" > Na22_correlation.txt
echo -n "180" >> Na22_correlation.txt
cd deg00
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "185" >> Na22_correlation.txt
cd deg05
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "190" >> Na22_correlation.txt
cd deg10
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "195" >> Na22_correlation.txt
cd deg15
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "200" >> Na22_correlation.txt
cd deg20
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "205" >> Na22_correlation.txt
cd deg25
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "210" >> Na22_correlation.txt
cd deg30
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "225" >> Na22_correlation.txt
cd deg45
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "240" >> Na22_correlation.txt
cd deg60
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "255" >> Na22_correlation.txt
cd deg75
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

echo -n "270" >> Na22_correlation.txt
cd deg90
../../../Code/easyfit.o histo.dat r pet
cd ..
#echo "3" >> Na22_correlation.txt

cat Na22_correlation.txt
