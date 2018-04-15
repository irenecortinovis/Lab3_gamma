#launch in terminal with python3 FWHM.py
import os, subprocess
path = os.getcwd()
list = os.listdir(path)
args = (path + "/../easyfit.o", "histo.dat", "r", "bias")

#Or just:
#args = "/../easyfit.o histo.dat r bias".split()

file = open("FWHM_vs_vbias.txt","w")
file.write("V_bias	FWHM 1	FWHM 2\n")

for dir in reversed(list):				#Seleziono solo le cartelle bias_****
    if dir.find(".") >= 0 or dir[0:4] != "bias":
        list.pop(list.index(dir))
list.sort()

for dir in list:
    buffer = dir[0:4]
    os.chdir(path)
    file = open("FWHM_vs_vbias.txt","a")		#Scrivo su file V_bias
    file.write(dir[-4:] + "\t")				#Scrivo su file V_bias
    file.close()
    os.chdir(path + "/" + dir)
    popen = subprocess.run(args, stdout=subprocess.PIPE) #Lancio easyfit.o sull'histo.dat della cartella 'dir'
    file = open(path + "/FWHM_vs_vbias.txt","a")
    file.write("\n")
    file.close()
