#!/bin/sh
#This script launches N957Demo data acquisition,
#visualizes the log in stdout and saves it in log.txt file
#You can create an alias in ~/.bashrc like this:
#alias acquire='/home/particelle2/Scrivania/Lab_2018/Lab_programs/acquire_data.sh'
#To get the script executable in bash, type:
#chmod +x acquire_data.sh

/home/particelle2/Scrivania/Lab_2018/Lab_programs/N957Demo | tee /home/particelle2/Scrivania/Lab_2018/Lab_programs/log.txt
echo "File log.txt generato"
#/home/particelle2/Scrivania/Lab_2018/Lab_programs/save_data.sh
