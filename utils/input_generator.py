import sys
sys.path.append('..')
sys.path.append('../..')
import random
import time
import math
import utils

import matplotlib.pyplot as plt
from student_utils import *

#################################################################
task = 0 # 0 for visualization, 1 for generate.
SIZE = 200
upper_bound = 200 # maximal weight
diff_weight = True # diffrent weight for edges. if false, weight is 1.0 for all edges
#################################################################


def visualize(input_file):
    input_data = utils.read_file(input_file)
    num_of_locations, num_houses, list_locations, list_houses, \
        starting_car_location, adjacency_matrix = data_parser(input_data)
    G, msg = adjacency_matrix_to_graph(adjacency_matrix)
    if msg == '':
        draw(G, name=input_file.split('/')[-1][:-2])
    else:
        print(msg)


def generate(input_directory, size):
    p = 0.3
    G = nx.fast_gnp_random_graph(size, p)
    G = assign_weight(G, size)
    while not nx.is_connected(G):
        G = nx.fast_gnp_random_graph(size, p)
        G = assign_weight(G, size)
    while not is_metric(G):
        G = assign_weight(G, size)
    # draw(G, name=str(size) + '.png')
    save_graph(G, size, input_directory)


def draw(G, name=''):
    plt.figure(figsize=(len(G)//2,len(G)//2))
    nx.draw(G, with_labels=True, font_weight='bold')
    fig = plt.gcf()
    plt.show()
    fig.savefig('../input/' + name)


def assign_weight(G, size):
    points = sample_points(size)
    for (u, v, w) in G.edges(data=True):
        w['weight'] = round(euler_dist(points[u], points[v]), 5)
    return G


def sample_points(size):
    random.seed(time.time())
    points = [(random.random()*size, random.random()*size) for i in range(size)]
    return points


def euler_dist(p1, p2):
    return math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2)


def save_graph(G, size, input_dictionary):
    num_loc = size
    num_home = size//2
    loc_name = [str(i) for i in range(num_loc)]
    home_name = [str(i) for i in range(num_loc)]
    random.shuffle(loc_name)
    random.shuffle(home_name)
    home_name = home_name[:num_home]
    start_loc = str(random.randint(0,size-1))

    data = ''
    data += str(num_loc) + '\n'
    data += str(num_home) + '\n'
    data += ' '.join(loc_name) + '\n'
    data += ' '.join(home_name) + '\n'
    data += start_loc + '\n'

    mat = nx.convert_matrix.to_numpy_matrix(G)
    data += parse_mat(mat)

    utils.write_to_file(input_directory + '/' + str(size) + '.in', data)


def parse_mat(mat):
    data = ''
    for row in range(mat.shape[0]):
        for col in range(mat.shape[1]):
            # print(mat.A[row][col])
            if mat.A[row][col] == 0.:
                data += 'x '
            else:
                if not diff_weight:
                    data += '1.00000 '
                else:
                    data += str(mat.A[row][col]) + ' '
        data += '\n'
    return data


if __name__=="__main__":
    input_directory = r"../input"
    output_directory = r"../output"

    if task == 0:
        file = 'sample.in'
        visualize(input_directory + '/' + file)
    elif task == 1:
        generate(input_directory, SIZE)

