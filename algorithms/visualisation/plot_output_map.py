import matplotlib.pyplot as plt
import matplotlib.colors as colors
import os

import numpy as np


def read_file_to_matrix(filename):
    matrix = []
    with open(filename, 'r') as file:
        for line in file:
            row = [int(digit) for digit in line.strip()]
            matrix.append(row)
    return matrix


def plot_matrix(matrix):

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
    plt.show()


dirname = os.path.dirname(__file__)
filename = os.path.join(dirname, 'outputs/mazePath.txt')
matrix = read_file_to_matrix(filename)

plot_matrix(matrix)
