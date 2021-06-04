import matplotlib.pyplot as plot

import IOHandler


def chart(lagrange_points, spline_points, interval_spline, full_spline_points,
          points_color='red', function_color='darkviolet', interpolation_color='blue'):
    data = [lagrange_points, spline_points, interval_spline, full_spline_points]
    titles = ['Lagrange interpolation',
              'Spline interpolation', 'Spline interpolation (interval)', 'Spline interpolation (all points)']

    for i in range(0, len(data)):
        plot.figure(i)
        plot.title(titles[i])
        plot.plot(data[i][0][1]['x'], data[i][0][1]['y'], color=interpolation_color, label='Interpolated function')
        plot.plot(data[i][0][0]['x'], data[i][0][0]['y'], color=function_color, label='Original function')
        plot.plot(data[i][0][0]['x'], data[i][0][0]['y'], 'o', color=points_color, label='Points', markersize=4)

        plot.xlabel('x')
        plot.ylabel('y')

        x1, x2, y1, y2 = plot.axis()
        plot.axis((x1, x2, min(data[i][0][0]['y']) - 10, max(data[i][0][0]['y']) + 10))
        plot.legend()

    plot.show()


if __name__ == "__main__":
    input_handler = IOHandler.IOHandler("../output/")
    chosen_file = input_handler.choose_file()

    chart([input_handler.read_lagrange(chosen_file)],
          [input_handler.read_spline(chosen_file, 'spline')],
          [input_handler.read_spline(chosen_file, 'interval_spline')],
          [input_handler.read_spline(chosen_file, 'full_spline')])
