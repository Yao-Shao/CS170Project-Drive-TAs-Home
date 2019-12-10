import os
import shutil

post_new = '_new3'
post_cur = '_cur'

opt_new = '../outputs' + post_new
opt_cur = '../outputs' + post_cur
cost_new = '../cost' + post_new + '.log'
cost_cur = '../cost' + post_cur + '.log'

opt_best = '../cost' + '_best'
cost_best = '../cost_best.log'

if os.path.isfile(cost_best):
	print('ERROR: {} exists'.format(cost_best))
	exit()
fcb = open(cost_best, 'w')

if os.path.exists(opt_best):
	print('ERROR: {} exists'.format(opt_best))
	exit()
else:
	os.mkdir(opt_best)

f1 = open(cost_new, 'r')
f2 = open(cost_cur, 'r')

for i in range(0, 946):
	tmp = f1.readline().split(':')
	fn1 = tmp[0]
	c1 = float(tmp[-1])
	tmp = f2.readline().split(':')
	fn2 = tmp[0]
	c2 = float(tmp[-1])
	if c1 < c2:
		print('{:10.3f}'.format((c1-c2)/c2 * 100),end=' ')
		print('copy ' + post_new)
		shutil.copy(opt_new+ '/' + fn1, opt_best)
		fcb.write(fn1 + ':' + str(c1) + '\n')
	else:
		# print('copy ' + post_cur)
		shutil.copy(opt_cur+ '/' + fn2, opt_best)
		fcb.write(fn2 + ':' + str(c2) + '\n')

f1.close()
f2.close()
fcb.close()
