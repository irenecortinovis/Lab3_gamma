#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Na22_correlation.txt
touch FWHM_vs_Energy.txt
echo "Energy	FWHM" > FWHM_vs_Energy.txt
cd Na22
../../../Code/easyfit.o histo.dat r fano
cd ..

cat FWHM_vs_Energy.txt