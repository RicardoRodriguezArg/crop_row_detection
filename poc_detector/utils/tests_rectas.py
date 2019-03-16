from vector_utils import sort_y_axis

def sort_vector(points):
    if points[0][0] > points[1][0]:
        temp = points[0][0]
        points[0] = points[1]
        points[1] = temp

def sort_points(points, index_1, index_2):
    if points[index_1][0] > points[index_2][0]:
        temp = points[index_1]
        points[index_1] = points[index_2]
        points[index_2] = temp
    return points


def sort_all_points(vector_points):
    index = 0
    total_size = len(vector_points)
    while (index < total_size ):
        vector_points = sort_points(vector_points, index , index + 1)
        index = index + 2
    return vector_points



if __name__ == "__main__":
    #points = [(51, 49), (40, 46), (93, 0), (104, 6)]
    points = [(0, 18), (25, 18), (0, 0), (25, 0)]
    #points = [(251, 49), (195, 1), (211, 0), (257, 35)]
    print points
    points = sort_y_axis(points)
    print points