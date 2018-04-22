#launch in terminal with python3 FWHM.py
import os, subprocess
path = os.getcwd()
list = os.listdir(path)
args = (path + "/../../Code/easyfit.o", "histo.dat", "r", "bias_nai")
#Or just:
#args = "/../../../Code/easyfit.o histo.dat r bias".split()

file = open("FWHM_vs_vbias.txt","w")
file.write("V_bias	gain	FWHM 1	err 1		FWHM 2	err 2\n")

for dir in reversed(list):
    if dir.find(".") >= 0:
        list.remove(dir)
list.sort()

print(list)
print(path)
for dir in list:
    os.chdir(path)
    sublist = os.listdir(path + "/" + dir)
    sublist.sort()
    for subdir in sublist:
        os.chdir(path)
        file = open("FWHM_vs_vbias.txt","a")
        file.write(dir + "\t" + subdir + "\t")			#Scrivo bias e gain nelle prime due colonne
        file.close()
        os.chdir(path + "/" + dir + "/" + subdir)
        popen = subprocess.run(args, stdout=subprocess.PIPE)	#Lancio easyfit.o sull'histo.dat della cartella 'dir/subdir'
        file = open(path + "/FWHM_vs_vbias.txt","a")
        file.write("\n")
        file.close()
        print("Analizzato bias " + dir)
