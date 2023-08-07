import matplotlib.pyplot as plt
import matplotlib.colors as colors
import os

import numpy as np


def process_maze(lines):
    matrix = []
    for line in lines:
        row = [int(digit) for digit in line.strip()]
        matrix.append(row)
    return matrix


def process_directions(lines):
    other_data = lines
    return other_data


def process_starting_direction(line):
    other_data = line
    return other_data


def process_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    end_maze_index = lines.index("==ENDMAZE\n")
    end_dirs_index = lines.index("==ENDDIRS\n")

    maze_lines = lines[:end_maze_index]
    direction_lines = lines[end_maze_index+1:end_dirs_index]
    starting_direction_lines = lines[end_dirs_index+1]

    data = {}
    data["maze"] = process_maze(maze_lines)
    data["instructions"] = process_directions(direction_lines)
    data["starting_direction"] = process_starting_direction(
        starting_direction_lines)

    return data


def plot_maze(matrix):

    cmap = colors.ListedColormap(['white', 'black', 'blue'])
    x_width = len(matrix[0])
    y_height = len(matrix)

    x_tick_positions = np.arange(0, x_width, 1)
    y_tick_positions = np.arange(0, y_height, 1)

    x_tick_labels = [str(i) for i in range(x_width)]
    y_tick_labels = [str(i) for i in range(y_height)]
    fig, ax = plt.subplots()

    ax.matshow(matrix, cmap=cmap)
    plt.xticks(x_tick_positions, x_tick_labels)
    plt.yticks(y_tick_positions, y_tick_labels)
    plt.title("Shortest Path")

    # Add the extra information as an annotation on the plot
    plt.show()


dirname = os.path.dirname(__file__)
filename = os.path.join(dirname, 'outputs/mazePath.txt')
data = process_file(filename)

print("Steps needed:")
print(data["instructions"])
print("Starting facing: " + data["starting_direction"])
plot_maze(data["maze"])
