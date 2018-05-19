#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Attenuation.txt
touch Attenuation.txt
echo "Depth	N_counts errDepth errN_counts" > Attenuation.txt
echo -n "20" >> Attenuation.txt
cd 20
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "30" >> Attenuation.txt
cd 30
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "55" >> Attenuation.txt
cd 55
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "84" >> Attenuation.txt
cd 84
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

echo -n "108" >> Attenuation.txt
cd 108
pwd
../../../../Code/easyfit.o histo.dat r att
cd ..

cat Attenuation.txt
