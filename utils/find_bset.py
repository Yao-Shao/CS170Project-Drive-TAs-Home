import os
import shutil

post1 = '1'
post2 = '2'

opt1 = '../outputs' + post1
opt2 = '../outputs' + post2
cost1 = '../cost' + post1 + '.log'
cost2 = '../cost' + post2 + '.log'

opt = '../outputs'
if not os.path.exists(opt):
	os.mkdir(opt)

f1 = open(cost1, 'r')
f2 = open(cost2, 'r')

for i in randge(949):
	tmp = f1.readline().split(':')
	fn = tmp[0]
	c1 = float(tmp[-1])
	c2 = float(f2.readline().split(':')[-1])
	print(c1,c2,end=' ')
	if c1 < c2:
		print('copy opt1')
		shutil.copy(opt1+ '/' + fn, opt)
	else:
		print('copy opt2')
		shutil.copy(opt2+ '/' + fn, opt)
