#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Attenuation.txt
touch Attenuation.txt
echo "Depth	N_counts errDepth errN_counts" > Attenuation.txt
echo -n "1.05" >> Attenuation.txt
cd 1_05
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "2.10" >> Attenuation.txt
cd 2_10
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "3.15" >> Attenuation.txt
cd 3_15
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "5.50" >> Attenuation.txt
cd 5_50
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "9.35" >> Attenuation.txt
cd 9_35
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

cat Attenuation.txt
./correlation.o
