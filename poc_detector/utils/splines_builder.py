import numpy as np
from scipy import interpolate
from scipy.interpolate import interp1d

class Spline():
    def __init__(self):
        self.__spline = None

    def process_points(self,x_set, y_set):
        self.__spline = interpolate.splrep(x_set, y_set, s=0)

    def get_estimated_point(self, x_point):
        y_point = interpolate.splev(x_point, self.__spline, der=0)
        return y_point

    @property
    def splines(self):
        return self.__splines
    

if __name__ == "__main__":
    spline = Spline()
    #x1 = [1., 0.88,  0.67,  0.50,  0.35,  0.27, 0.18,  0.11,  0.08,  0.04,  0.04,  0.02]
    x1 = sorted([1., 0.88, 0.67, 0.50, 0.35, 0.27, 0.18, 0.11, 0.08, 0.04, 0.04, 0.02])
    y1 = [0., 13.99, 27.99, 41.98, 55.98, 69.97, 83.97, 97.97, 111.96, 125.96, 139.95, 153.95]
    x = np.array(x1)
    y = np.array(y1)
    spline.process_points(x, y)