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

    @staticmethod
    def sequence(start, stop, step):
        n = int(round((stop - start) / float(step)))
        if n > 1:
            return [start + step * i for i in range(n + 1)]
        elif n == 1:
            return [start]
        else:
            return []

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
        file = open(directory + '/lagrange_factors.txt', "r")
        for line in file:
            factors.append(float(line.strip()))

        file.close()

        lagrange_x_points = self.sequence(int(points['x'][0]), int(points['x'][-1]), 1 / density)
        lagrange_points = {
            'x': lagrange_x_points,
            'y': self.values_lagrange(lagrange_x_points, factors)
        }

        return points, lagrange_points

    @staticmethod
    def values_spline(x_0, x_i, factors):
        h = x_i - x_0

        y = 0
        for j in range(0, len(factors)):
            y += factors[j] * h ** (len(factors) - j - 1)

        return y

    def read_spline(self, directory, mode, density=10):
        factors = []

        if density < 1:
            density = 1

        # read default points
        points = self.__read_points(mode, directory)

        # calculate spline points
        current_factor = []
        i = 0

        file = open(directory + '/' + mode + '_factors.txt', "r")
        for line in file:
            if i >= 4:
                current_factor.reverse()
                factors.append(current_factor)

                current_factor = []
                i = 0

            current_factor.append(float(line.strip()))
            i += 1

        current_factor.reverse()
        factors.append(current_factor)
        file.close()

        spline_points = {
            'x': self.sequence(int(points['x'][0]), int(points['x'][-1]), 1 / density),
            'y': []
        }

        i = 1
        while i < len(points['x']) - 1:
            for x_i in [x for x in spline_points['x'] if points['x'][i - 1] <= x <= points['x'][i]]:
                spline_points['y'].append(
                    self.values_spline(
                        points['x'][i - 1],
                        x_i,
                        factors[i - 1]
                    )
                )
            i += 1

        for x_i in [x for x in spline_points['x'] if points['x'][-2] < x]:
            spline_points['y'].append(
                self.values_spline(
                    points['x'][-2],
                    x_i,
                    factors[-1]
                )
            )

        return points, spline_points
