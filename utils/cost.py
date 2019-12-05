import sys
sys.path.append('..')
sys.path.append('../..')
import argparse
import utils
from student_utils import *
import input_validator
import tqdm
import re
import os


def validate_output(input_file, output_file, params=[]):
    # print('Processing', input_file)

    input_data = utils.read_file(input_file)
    output_data = utils.read_file(output_file)

    cost = tests(input_data, output_data, params=params)

    return cost


def validate_all_outputs(input_directory, output_directory, check_dir, params=[]):
    input_files = utils.get_files_with_extension(input_directory, '.in')
    output_files = utils.get_files_with_extension(output_directory, '.out')
    if os.path.isfile(check_dir):
        print('ERROR: ' + check_dir + 'already exist!')
        return

    check_file = open(check_dir, 'w')

    for input_file in tqdm.tqdm(input_files):
        output_file = utils.input_to_output(input_file, output_directory)
        # print(input_file, output_file)
        if output_file not in output_files:
            print(f'No corresponding .out file for {input_file}')
        else:
            cost = validate_output(input_file, output_file, params=params)
            name = input_file.split('/')[-1]
            check_file.write(name + ':' + str(cost) + '\n')
    check_file.close()

def tests(input_data, output_data, params=[]):
    number_of_locations, number_of_houses, list_of_locations, list_of_houses, starting_location, adjacency_matrix = data_parser(input_data)
    try:
        G, message = adjacency_matrix_to_graph(adjacency_matrix)
    except Exception:
        return 'Your adjacency matrix is not well formed.\n', 'infinite'
    message = ''
    cost = -1
    car_cycle = output_data[0]
    num_dropoffs = int(output_data[1][0])
    
    targets = []
    dropoffs = {}
    for i in range(num_dropoffs):
        dropoff = output_data[i + 2]
        dropoff_index = list_of_locations.index(dropoff[0])
        dropoffs[dropoff_index] = convert_locations_to_indices(dropoff[1:], list_of_locations)

    car_cycle = convert_locations_to_indices(car_cycle, list_of_locations)

    if cost != 'infinite':
        cost, solution_message = cost_of_solution(G, car_cycle, dropoffs)

    return cost


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Parsing arguments')
    parser.add_argument('input', type=str, help='The path to the input file or directory')
    parser.add_argument('output', type=str, help='The path to the output file or directory')
    parser.add_argument('check', type=str, help='the path to the output file check log')
    parser.add_argument('params', nargs=argparse.REMAINDER, help='Extra arguments passed in')
    args = parser.parse_args()
    input_directory, output_directory = args.input, args.output
    check_dir = args.check
    validate_all_outputs(input_directory, output_directory, check_dir, params=args.params)