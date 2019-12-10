import argparse
import os
import subprocess
import tqdm

parser = argparse.ArgumentParser(description='Parsing arguments')
parser.add_argument('inputs', type=str, help='The path to the input directory')
parser.add_argument('outputs', type=str, help='The path to the output directory')
args = parser.parse_args()

path_in = args.inputs
path_out = args.outputs
path_log = '../cost_new.log'
path_best = '../outputs_best/'

if not os.path.exists(path_best):
	print('ERROR: can\'t find the best output folder')
	exit()

if not os.path.exists(path_out):
	print('create new folder at {}'.format(path_out))
	os.mkdir(path_out)

post_fix_list = ['50','100','200']

# generate output
cwd = os.getcwd()

os.chdir(cwd[:-5] + 'alg')

for gid in tqdm.tqdm(range(1,367)):
	for pf in post_fix_list:
		n_in = path_in + '/' + str(gid) + '_' + pf + '.in'
		if not os.path.isfile(n_in):
			continue
		n_out = path_out + '/' + str(gid) + '_' + pf + '.out'
		job = 'project.exe ' +  n_in + ' ' + n_out
		os.system(job)

os.chdir(cwd)

# get cost for each output
job = 'python cost.py ' + path_in	+ ' ' + path_out + ' ' + path_log
os.system(job)

# update output by log file
job = 'python find_best_partial.py ' + path_out + ' ' + path_log 
os.system(job)

# compress best output
job = 'python compress_output.py ' + path_best
os.system(job)