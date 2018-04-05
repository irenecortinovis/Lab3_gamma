#!/bin/sh
#To get the script executable in bash, type:
#chmod +x FWHM.sh

mv results.txt results.txt.save
echo "bias      FWHM peak 1     FWHM peak 2" > results.txt
#n=$(ls -dq *bias* | wc -l)             #numero di cartelle bias_*
bias=3500
gap=100
for i in $(seq 10)
do
        echo -n $bias   >> results.txt
        echo -n "\t" >> results.txt
        ./easyfit_peak1 ./bias_$bias/histo.dat r
        echo -n "\t\t" >> results.txt
        ./easyfit_peak2 ./bias_$bias/histo.dat r
        echo >> results.txt
        bias=`expr $bias + $gap`
done
