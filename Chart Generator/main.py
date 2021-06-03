import matplotlib.pyplot as plot

import IOHandler


def chart(original_points, function_points):
    plot.figure()
    plot.plot(function_points['x'], function_points['y'])
    plot.plot(original_points['x'], original_points['y'], 'ro', markersize=4)

    x1, x2, y1, y2 = plot.axis()
    plot.axis((x1, x2, min(original_points['y']) - 10, max(original_points['y']) + 10))
    plot.show()


if __name__ == "__main__":
    input_handler = IOHandler.IOHandler("../output/")
    chosen_file = input_handler.choose_file()

    # points, function = input_handler.read_lagrange(chosen_file)
    # chart(points, function)

    points, function = input_handler.read_spline(chosen_file, 1)
    chart(points, function)
