from math import *

import matplotlib.pyplot as plt

# print(alpha)
# print(rocket_weight)
# print(fuel_weight)
# print(gas_velocity)
# print(burn_velocity)
# print(earth_weight)

x = []
y = []
speed = []
fuel_left = []

#  CONST
earth_radius = 6.37 * 10 ** 6
G = 6.67 * 10 ** (-11)


def calculate_g(prev_y, earth_weight):
    return G * earth_weight / (earth_radius + prev_y) ** 2


def calculate_speed(cur_rocket_weight, gas_velocity, rocket_weight):
    return gas_velocity * log1p(cur_rocket_weight / rocket_weight)


def calculate_acceleration(full_rocket_weight, prev_y, gas_velocity, burn_velocity, earth_weight):
    return (gas_velocity * burn_velocity - full_rocket_weight * calculate_g(prev_y, earth_weight)) / full_rocket_weight


def calculate_left_fuel(cur_time, fuel_weight, burn_velocity):
    return fuel_weight - cur_time * burn_velocity


def calculate_x(cur_acceleration, cur_time, alpha):
    return (cur_acceleration * cos(alpha) * cur_time ** 2) / 2


def calculate_y(cur_acceleration, cur_time, alpha):
    return (cur_acceleration * sin(alpha) * cur_time ** 2) / 2


def graph(alpha, rocket_weight, fuel_weight, gas_velocity, burn_velocity, earth_weight):
    full_rocket_weight = rocket_weight + fuel_weight
    up_flight_time = int(fuel_weight / burn_velocity)
    print(up_flight_time)
    for second in range(up_flight_time):
        if second == 0:
            x.append(0)
            y.append(0)
            speed.append(0)
            fuel_left.append(fuel_weight)
        else:
            cur_rocket_weight = rocket_weight + fuel_left[second - 1]
            a = calculate_acceleration(cur_rocket_weight, y[second - 1], gas_velocity, burn_velocity, earth_weight)
            x.append(calculate_x(a, second, alpha))
            y.append(calculate_y(a, second, alpha))
            speed.append(calculate_speed(cur_rocket_weight, gas_velocity, rocket_weight))
            fuel_left.append(calculate_left_fuel(second, fuel_weight, burn_velocity))
    print(len(x), len(y))
    plt.plot(x, y)
    plt.show()
