import os
import shutil
import argparse

parser = argparse.ArgumentParser(description='Parsing arguments')
parser.add_argument('opt_new', type=str, help='The path to the new output directory')
parser.add_argument('log_new', type=str, help='The path to the new log file')
args = parser.parse_args()

opt_new = args.opt_new
log_new = args.log_new

opt_best = '../outputs' + '_best'
log_best = '../cost_best.log'

if not os.path.exists(opt_best):
	print('create: {}'.format(opt_best))
	os.mkdir(opt_best)

f_new = open(log_new, 'r')
f_best = open(log_best, 'r')

lines_new = f_new.readlines()
lines_best = f_best.readlines()

cnt = 0

for line_new in lines_new:
	fn = line_new.split(':')[0]
	if line_new.split(':')[-1].find('infinite') == -1:
		cost_new = float(line_new.split(':')[-1])
		cost_best = float([i.split(':')[-1] for i in lines_best if i.split(':')[0] == fn][0])
		if cost_new < cost_best:
			cnt += 1
			print('{:10.3f}'.format((cost_new-cost_best)/cost_best * 100),end=' ')
			print('copy ' + fn)
			os.remove(opt_best+ '/' + fn)
			shutil.copy(opt_new + '/' + fn, opt_best)
			for i in lines_best:
				if i.split(':')[0] == fn:
					lines_best[lines_best.index(i)] = i.split(':')[0] + ':' + str(cost_new) + '\n'
print(cnt, 'files has been updated')

f_best.close()
f_best = open(log_best, 'w')
f_best.writelines(lines_best)

f_new.close()
f_best.close()
