#launch in terminal with
#python3 ENC.py
import os, subprocess
path = os.getcwd()
list = os.listdir(path)
args = (path + "/../../../easyfit.o", "histo.dat", "r", "enc")

file = open("ENC_vs_ST.txt","w")
file.write("ST	FWHM	err ST\n")

for dir in reversed(list):
    if dir.find(".") >= 0 or dir[0:9] != "amplitude":
        list.remove(dir)
list.sort()

for dir in list:
    os.chdir(path)
    sublist = os.listdir(path + "/" + dir)
    sublist.sort()
    for subdir in sublist:
        os.chdir(path)
        file = open("ENC_vs_ST.txt","a")
        shap = subdir.split("_")
        ST = shap[-2] + "." + shap[-1]
        file.write(ST + "\t")			#Scrivo ST nella prima colonna del file
        file.close()
        os.chdir(path + "/" + dir + "/" + subdir)
        popen = subprocess.run(args, stdout=subprocess.PIPE)
        file = open(path + "/ENC_vs_ST.txt","a")
        file.write("0.1\n")			#Scrivo errST nella terza colonna del file
        file.close()
