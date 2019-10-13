from scipy.special import fresnel
from scipy import linspace
import matplotlib.pyplot as plt
import argparse

def create_clothoid_points(lower_bound, upper_bound, curve_value):
	t = linspace(lower_bound, upper_bound, curve_value)
	y_set_point, x_set_point = fresnel(t)
	return y_set_point, x_set_point



def parse_arguments():
	parser = argparse.ArgumentParser(description='Create Set Of Point using Euler Spiral. The output will be stored as a list of tuples')
	parser.add_argument('--lower_bound', type=int, default=-5, help='Lower bound value for calculate Euler Spiral')
	parser.add_argument('--upper_bound', type=int, default=5, help='Upper bound value for calculate Euler Spiral')
	parser.add_argument('--curve_value', type=int, default=300, help='Number of points to be generated')
	parser.add_argument('--output', default='output.txt', help='Output of the generated list')
	args = parser.parse_args()
	return args

def save_output(output_filename, x_set_point, y_set_point):
	file = open(output_filename, "w")
	for xpoint in x_set_point:
		for ypoint in y_set_point:
			file.write(str(xpoint) + "," + str(ypoint)+"\n")
	file.close()


if __name__ == '__main__':
	arguments = parse_arguments()
	y_set_point, x_set_point = create_clothoid_points(arguments.lower_bound,arguments.upper_bound, arguments.curve_value)
	save_output(arguments.output, x_set_point, y_set_point)


