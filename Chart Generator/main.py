import matplotlib.pyplot as plot
import math
import IOHandler


def chart(data, points_color='black', interpolation_nodes_color='red', interpolation_color='dodgerblue', point_size=3):
    for i in range(0, 5):
        plot.figure(i)
        plot.title(data['title'][i] + " interpolation")

        plot.plot(data['interpolated_function'][i]['x'],
                  data['interpolated_function'][i]['y'],
                  color=interpolation_color, label='Interpolated function')

        plot.plot(data['origin_nodes'][i]['x'],
                  data['origin_nodes'][i]['y'],
                  'o', color=points_color, label='Origin nodes', markersize=point_size)

        if data['title'][i].__contains__('interval'):
            plot.plot(data['interpolation_nodes'][i]['x'],
                      data['interpolation_nodes'][i]['y'],
                      'o', color=interpolation_nodes_color, label='Interpolation nodes', markersize=point_size)

        plot.xlabel('x')
        plot.ylabel('y')

        x1, x2, y1, y2 = plot.axis()
        plot.axis((x1, x2, min(data['origin_nodes'][i]['y']) - 10, max(data['origin_nodes'][i]['y']) + 10))
        plot.legend()

    plot.show()


def update_interpolation_data(interpolation_data, original_points, interpolation_nodes, interpolated_function):
    interpolation_data['origin_nodes'].append(original_points)
    interpolation_data['interpolation_nodes'].append(interpolation_nodes)
    interpolation_data['interpolated_function'].append(interpolated_function)


def rmsd(original_nodes, function):
    result = 0

    for i, node in enumerate(original_nodes['x']):
        index = function['x'].index(min(function['x'], key=lambda x_i: abs(x_i - node)))
        result += (function['y'][index] - original_nodes['y'][i]) ** 2

    return math.sqrt(result / len(original_nodes['x']))


if __name__ == "__main__":
    input_handler = IOHandler.IOHandler("../output/")
    chosen_file = input_handler.choose_file()

    print()

    function_data = {
        'title': ['Lagrange', 'Lagrange (interval)', 'Spline', 'Spline (interval)', 'Spline (all points)'],
        'origin_nodes': [],
        'interpolation_nodes': [],
        'interpolated_function': []
    }

    all_points_spline = input_handler.read_points(chosen_file, 'full_spline')

    origin_points, function_points = input_handler.read_lagrange(chosen_file, 'lagrange')
    update_interpolation_data(function_data, origin_points, origin_points, function_points)

    print("=== RMSD ===")
    print("Lagrange function: " + str(rmsd(origin_points, function_points)))

    all_points_lagrange = origin_points

    origin_points, function_points = input_handler.read_lagrange(chosen_file, 'interval_lagrange')
    update_interpolation_data(function_data, all_points_lagrange, origin_points, function_points)
    print("Lagrange function (interval): " + str(rmsd(origin_points, function_points)))

    origin_points, function_points = input_handler.read_spline(chosen_file, 'spline')
    update_interpolation_data(function_data, origin_points, origin_points, function_points)
    print("Spline function: " + str(rmsd(origin_points, function_points)))

    origin_points, function_points = input_handler.read_spline(chosen_file, 'interval_spline')
    update_interpolation_data(function_data, all_points_spline, origin_points, function_points)
    print("Spline function (interval): " + str(rmsd(origin_points, function_points)))

    origin_points, function_points = input_handler.read_spline(chosen_file, 'full_spline')
    update_interpolation_data(function_data, all_points_spline, origin_points, function_points)
    print("Spline function (full): " + str(rmsd(origin_points, function_points)))

    chart(function_data)
