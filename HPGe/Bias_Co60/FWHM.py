#launch in terminal with
#python3 FWHM.py
import os, subprocess
path = os.getcwd()
list = os.listdir(path)
args = (path + "/../easyfit.o", "histo.dat", "r", "bias")

#Or just:
#args = "bin/bar -c somefile.xml -d text.txt -r aString -f anotherString".split()

file = open("FWHM_vs_vbias.txt","w")
file.write("V_bias	FWHM 1	FWHM 2\n")

for dir in list:
    if dir.find(".") >= 0:
        list.pop(list.index(dir))

list.sort()

for dir in list:
    buffer = dir[0:4]
    os.chdir(path)
    if buffer != "bias":
        list.pop(list.index(dir))
    else:
        file = open("FWHM_vs_vbias.txt","a")
        file.write(dir[-4:] + "\t")
        file.close()
        os.chdir(path + "/" + dir)
        popen = subprocess.run(args, stdout=subprocess.PIPE)
