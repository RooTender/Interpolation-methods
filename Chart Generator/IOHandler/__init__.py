import os


class IOHandler:

    def __init__(self, directory):
        self.directory = directory
        self.dir_files = [subdir[0] for subdir in os.walk(directory) if subdir[0] != directory]

    def __is_input_valid(self, selected):
        if not selected.isnumeric():
            print("Bad input! Given: " + selected)
            return False

        if int(selected) < 0 or int(selected) > len(self.dir_files) - 1:
            print("Position out of range!")
            print("Available range: [0, " + str(len(self.dir_files) - 1) + "]")
            return False

        return True

    def choose_file(self):
        print("List of available data for analysis:")

        files = []
        for iteration, file in enumerate(self.dir_files):
            files.append(file)

            filename = file.replace(self.directory, '')
            print(str(iteration) + ". " + filename)

        print()

        position = input("Choose position (enter number): ")
        if not self.__is_input_valid(position):
            exit()

        return files[int(position)]

    # def add_midpoints(self, given_points):
    #     result = copy.deepcopy(given_points)
    #     midpoints = []
    #
    #     for i in range(1, len(given_points)):
    #         midpoints.append((given_points[i - 1] + given_points[i]) / 2)
    #
    #     for i in range(len(given_points) - 1):
    #         result.insert(2 * i + 1, midpoints[i])
    #
    #     return result

    @staticmethod
    def __read_points(function, directory):
        points = {
            'x': [],
            'y': []
        }

        file = open(directory + "/" + function + "_points.txt", "r")
        for line in file:
            line = line.split(' ')

            points['x'].append(float(line[0].strip()))
            points['y'].append(float(line[1].strip()))

        file.close()

        return points

    @staticmethod
    def values_lagrange(x_points, factors):
        y = []
        for x in x_points:
            value = 0
            for i in range(0, len(factors)):
                value += factors[i] * x ** (len(factors) - i - 1)

            y.append(value)

        return y

    def read_lagrange(self, directory, density=10):
        factors = []

        if density < 1:
            density = 1

        # read default points
        points = self.__read_points('lagrange', directory)

        # calculate lagrange points
        file = open(directory + "/lagrange_factors.txt", "r")
        for line in file:
            factors.append(float(line.strip()))

        file.close()

        lagrange_x_points = [i / density for i in range(int(points['x'][0]), (int(points['x'][-1]) + 1) * density)]
        lagrange_points = {
            'x': lagrange_x_points,
            'y': self.values_lagrange(lagrange_x_points, factors)
        }

        return points, lagrange_points

    def values_spline(self, x_interval, factors):
        y = [factors[0]]

        for i in range(0, len(x_interval) - 1):
            h = x_interval[i + 1] - x_interval[i]

            value = 0
            for j in range(0, len(factors)):
                value += factors[j] * h ** (len(factors) - j - 1)

            y.append(value)

        return y

    def read_spline(self, directory, density=10):
        factors = []

        if density < 1:
            density = 1

        # read default points
        points = self.__read_points('spline', directory)

        # calculate spline points
        current_factor = []
        first_spline = True

        file = open(directory + "/spline_factors.txt", "r")
        for line in file:
            value = line.strip()

            if value == ';':
                if first_spline:
                    factors.append(current_factor[:(len(current_factor) // 2)])
                    first_spline = False

                factors.append(current_factor[(len(current_factor) // 2):])
                current_factor = []

            else:
                current_factor.append(float(value))

        file.close()

        spline_points = {
            'x': [i / density for i in range(int(points['x'][0]), (int(points['x'][-1]) + 1) * density)],
            'y': []
        }

        i = 1
        while i < len(points['x']) - 1:
            spline_points['y'].extend(
                self.values_spline(
                    [x for x in spline_points['x'] if points['x'][i - 1] <= x <= points['x'][i]],
                    factors[i - 1]
                )
            )
            i += 1

        spline_points['y'].extend(
            self.values_spline(
                [x for x in spline_points['x'] if points['x'][-2] <= x],
                factors[-1]
            )
        )

        return points, spline_points
