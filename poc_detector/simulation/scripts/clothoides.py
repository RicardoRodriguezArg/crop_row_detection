from scipy.special import fresnel
from scipy import linspace
import matplotlib.pyplot as plt
import argparse

def create_points(lower_bound, upper_bound, number_of_points):
	t = linspace(lower_bound, upper_bound,  number_of_points)
	y_set_point, x_set_point = fresnel(t)
	return y_set_point, x_set_point

plt.plot(x, y)
plt.axes().set_aspect("equal")
plt.show()



if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Create Set Of Point using Euler Spiral.')
	parser.add_argument('--lower_bound', type=int, help='Lower bound value for calculate Euler Spiral')
	parser.add_argument('--upper_bound', type=int, help='Upper bound value for calculate Euler Spiral')
	parser.add_argument('--count', type=int, help='Number of points to be generated')
	parser.add_argument('--output', type=int, help='Output of the generated list')
	args = parser.parse_args()
	y_set_point, x_set_point = create_clothoid_points()


