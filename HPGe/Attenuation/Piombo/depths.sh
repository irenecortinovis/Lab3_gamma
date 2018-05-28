#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Attenuation.txt
touch Attenuation.txt
echo "Depth	N_counts errDepth errN_counts" > Attenuation.txt
echo -n "1.25" >> Attenuation.txt
cd 1_25
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "2.55" >> Attenuation.txt
cd 2_55
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "4.85" >> Attenuation.txt
cd 4_85
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "25.85" >> Attenuation.txt
cd 25_85
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "30.70" >> Attenuation.txt
cd 30_7
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

cat Attenuation.txt
./correlation.o
