from argparse import ArgumentParser
parser = ArgumentParser()
parser.add_argument("inputname", help="csv file to transpose")
parser.add_argument("outname", help="filename to save")
parser.add_argument("eps", help="eps filename")
args = parser.parse_args()
import pandas as pd
inputname = args.inputname
outname = args.outname
eps = args.eps
df = pd.read_csv(inputname, header=None)
df = df.transpose()
df.to_csv(outname, index = False, header=False)
filename = "aoto_eps\\gnu_template.gp"
myfile = open(filename, 'r')
mygp = open("aoto_eps\\plot_eps.gp", 'w')
mygp.write("filename = \'" + outname + "\'\noutname = \'" + eps + "\'\ncolumns = " + str(len(df.columns)) + "\n" + myfile.read())
myfile.close()
mygp.close()
import subprocess
subprocess.run(["gnuplot", "aoto_eps\\plot_eps.gp"])