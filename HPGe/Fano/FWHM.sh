#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Na22_correlation.txt
touch FWHM_vs_Energy.txt
echo "Energy	err_Energy FWHM  err_FWHM" > FWHM_vs_Energy.txt
cd Na22
../../../Code/easyfit.o histo.dat r fanohpge
cd ..

cd K40
../../../Code/easyfit.o histo.dat r fanohpge
cd ..

cd Co60
../../../Code/easyfit.o histo.dat r fanohpge
cd ..

cd Th228
../../../Code/easyfit.o histo.dat r fanohpge
cd ..

cat FWHM_vs_Energy.txt
