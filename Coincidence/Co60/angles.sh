#!/bin/sh
#Script per generare il TGraph counts_vs_theta
#Viene creato il file Co60_correlation.txt
touch Co60_correlation.txt
echo "Theta	peak1	peak2	sb1		sb2" > Co60_correlation.txt
echo -n "180" >> Co60_correlation.txt
cd deg00
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "190" >> Co60_correlation.txt
cd deg10
../../../Code/easyfit.o histo.dat r Co60
cd ..

#echo -n "200" >> Co60_correlation.txt
#cd deg20_retake2
#../../../Code/easyfit.o histo.dat r Co60
#cd ..

echo -n "210" >> Co60_correlation.txt
cd deg30
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "220" >> Co60_correlation.txt
cd deg40
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "230" >> Co60_correlation.txt
cd deg50
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "240" >> Co60_correlation.txt
cd deg60_retake3
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "250" >> Co60_correlation.txt
cd deg70
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "260" >> Co60_correlation.txt
cd deg80
../../../Code/easyfit.o histo.dat r Co60
cd ..

echo -n "270" >> Co60_correlation.txt
cd deg90
../../../Code/easyfit.o histo.dat r Co60
cd ..

cd HPGe_alone
../../../Code/easyfit.o histo.dat r Co60ratio
cd ..

cat Co60_correlation.txt
echo "ratio = $(cat ratio.txt)"
./correlation.o
