#!/bin/sh
#This script saves histo.dat and log.txt file in the indicated directory
#You can create an alias in ~/.bashrc like this:
#alias save='/home/particelle2/Scrivania/Lab_2018/Lab_programs/save_data.sh'
#To get the script executable in bash, type:
#chmod +x save_data.sh

echo "Inserisci il path della cartella rispetto alla cartella corrente:"
echo "pwd: $PWD"
read dir
cp /home/particelle2/Scrivania/Lab_2018/Lab_programs/histo.dat ./$dir
cp /home/particelle2/Scrivania/Lab_2018/Lab_programs/log.txt ./$dir
