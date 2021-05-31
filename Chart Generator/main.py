import copy

import matplotlib.pyplot as plot


def get_list_of_available_functions(path):
    result = []

    try:
        file = open(path, "r")
        for line in file:
            result.append(line)
        file.close()

    except FileNotFoundError:
        print("It seems the database is empty!")
        print("Please generate at least one interpolated function using C++ program.")

    return result


def is_input_valid(data, given_input):
    if not given_input.isnumeric():
        print("Bad input! Given: " + position)
        return False

    if int(given_input) < 0 or int(given_input) > len(data) - 1:
        print("Position out of range!")
        print("Available range: [0, " + str(len(data) - 1) + "]")
        return False

    return True


def read_points(filename):
    x = []
    y = []

    file = open(filename + "_points.txt", "r")
    for line in file:
        line = line.split(' ')

        x.append(float(line[0].strip()))
        y.append(float(line[1].strip()))

    file.close()

    return x, y


def get_function(x_array, factors):
    y = []
    for x in x_array:
        value = 0
        for i in range(0, len(factors)):
            value += factors[i] * x ** (len(factors) - i - 1)

        y.append(value)

    return y


def add_midpoints(given_points):
    result = copy.deepcopy(given_points)
    midpoints = []

    for i in range(1, len(given_points)):
        midpoints.append((given_points[i - 1] + given_points[i]) / 2)

    for i in range(len(given_points) - 1):
        result.insert(2 * i + 1, midpoints[i])

    return result


def read_lagrange(input_points, filename):
    function_factors = []

    file = open(filename + "_lagrange.txt", "r")
    for line in file:
        function_factors.append(float(line.strip()))
    file.close()

    denominator = 10
    x = [i / denominator for i in range(int(input_points[0]), (int(input_points[-1]) + 1) * denominator)]
    y = get_function(x, function_factors)

    return x, y


if __name__ == "__main__":

    directory_with_files = "../output/"
    available_data = get_list_of_available_functions(directory_with_files + "available.txt")
    files = []

    print("List of available data for analysis:")
    for iteration, title in enumerate(available_data):
        print(str(iteration) + ". " + title)
        files.append(directory_with_files + title.rstrip())

    position = input("Choose position (enter number): ")
    if not is_input_valid(available_data, position):
        exit()

    chosen_file = files[int(position)]
    x_points, y_points = read_points(chosen_file)
    x_lagrange, y_lagrange = read_lagrange(x_points, chosen_file)

    plot.figure()
    plot.plot(x_lagrange, y_lagrange)
    plot.plot(x_points, y_points, 'ro', markersize=4)
    x1, x2, y1, y2 = plot.axis()
    plot.axis((x1, x2, min(y_points) - 10, max(y_points) + 10))
    plot.show()
