import sys
sys.path.append('..')
sys.path.append('../..')
import utils

from student_utils import *

size = [50,100,200]
input_directory = [r"../input/" + str(i) + ".in" for i in size]
output_directory = [r"../output/" + str(i) + ".out" for i in size]

if __name__ == '__main__':
    for i,f_in in enumerate(input_directory):
        input_data = utils.read_file(f_in)
        num_of_locations, num_houses, list_locations, list_houses, \
            starting_car_location, adjacency_matrix = data_parser(input_data)
        f_out = open(output_directory[i], 'w')

        data = ''
        data += starting_car_location + '\n'
        data += '1\n'
        data += starting_car_location + ' ' + ''.join([i + ' ' for i in list_houses])

        f_out.write(data[:-1])
        f_out.close()






