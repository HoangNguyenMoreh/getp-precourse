#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt
def draw(benchmark_label, unit_label, input_line_offset, is_reverse_y_axis):
    n_strides = 64
    xticks = list((map(lambda stride: "s" + str(stride), range(1, n_strides + 1))))
    yticks = "2KiB 4KiB 8KiB 16KiB 32KiB 64KiB 128KiB 256KiB 512KiB 1MiB 2MiB 4MiB 8MiB 16MiB 32MiB 64MiB 128MiB".split()
    n_sizes = len(yticks)
    x = np.arange(1, n_strides + 1)  # stride
    y = np.arange(1, n_sizes + 1)  # size ticks
    x, y = np.meshgrid(x, y)
    f = open("memory_mountain.txt", "r")
    z0 = f.read()
    z1 = z0.splitlines()[input_line_offset:input_line_offset + n_sizes]
    # Divide by tab, discard first and last column
    z2 = np.array(list(map(lambda line: line.split(" ")[1:n_strides+1], z1)))
    z2 = z2.astype(float)
    z2 = z2.astype(int)
    if is_reverse_y_axis:
        z2 = np.flip(z2, 0)
        yticks = yticks[::-1]
    fig = plt.figure()
    ax = plt.axes(projection="3d")
    ax.set_xticks(range(1, n_strides + 1, 2))
    ax.set_yticks(range(1, n_sizes + 1))
    # Take only every other label
    plt.rcParams.update({"font.size": 16})
    ax.set_xticklabels(xticks[::2], fontsize=2)
    ax.set_yticklabels(yticks, fontsize=3)
    ax.tick_params(axis="z", pad=10)
    ax.set_xlabel("Stride", fontsize=8, labelpad=20)
    ax.set_ylabel("Size", fontsize=8, labelpad=20)
    ax.set_zlabel(benchmark_label + " (" + unit_label + ")", fontsize=8, labelpad=20)
    ax.set_title("Memory Mountain\n", fontsize=16)
    ax.plot_surface(x, y, z2, cmap="jet")
    plt.tight_layout()
    plt.savefig("graph_" + benchmark_label + ".pdf")


def main():
    draw("Throughput", "MiB/s", 1+1, True)
    draw("Latency", "picosec", 1+1+17+1, False)
    print("Finished!!")

if __name__ == "__main__":
    main()