import numpy as np

def sort_y_axis(vector_points):
    index_first = get_y_small_value(vector_points, 0)
    vector_points = rotate(vector_points, index_first)
    temporal = vector_points[1:]
    index_first = 0
    index_second = get_y_small_value(temporal,0)
    temporal = rotate(temporal, index_second)
    vector_points = vector_points[:1]+ temporal
    vector_points = sort_pair_of_value(vector_points,axis=1)
    vector_points = sort_pair_of_value(vector_points,axis=0)
    return vector_points

def sort_pair_of_value(vector_points, axis=1):
    index = 0
    while index < len(vector_points):
        if vector_points[index][axis] > vector_points[index + 1 ][axis]:
            temporal = vector_points[index]
            vector_points[index] = vector_points[index + 1]
            vector_points[index + 1] = temporal
        index = index + 2
    return vector_points


def rotate(l, n):
    return l[n:] + l[:n]

def get_y_small_value(vector_points, index):
    for index_vector in xrange(len(vector_points)):
        if index != index_vector :
            if vector_points[index][1] > vector_points[index_vector][1]:
                index = index_vector
    return index
    


def get_middle_point(points):
    delta_x = points[1][0] - points[0][0]
    delta_y = points[1][1] - points[0][1]
    m = delta_y / delta_x
    b = points[0][1]
    middle_x_point = delta_x / 2.0
    midle_y_point = m*(middle_x_point - points[0][0]) + b
    return int(middle_x_point), int(midle_y_point)

def is_valid_boundary_box(points, heigth_value, heigth_threshold):
    dist_1 = np.linalg.norm(np.asarray(points[1], dtype=np.float32) - np.asarray(points[0], dtype=np.float32))
    dist_2 = np.linalg.norm(np.asarray(points[3], dtype=np.float32) - np.asarray(points[2], dtype=np.float32))
    heigth_value_one = np.linalg.norm(np.asarray(points[2], dtype=np.float32) - np.asarray(points[0], dtype=np.float32))
    heigth_value_two = np.linalg.norm(np.asarray(points[3], dtype=np.float32) - np.asarray(points[1], dtype=np.float32))
    is_valid = True
    if( heigth_value_one < (heigth_value - heigth_threshold)):
        is_valid = False
    return is_valid

def line_parameter_from_points(init_point, end_point):
    delta_x = init_point[0] - end_point[0]
    delta_y = init_point[1] - end_point[1]
    m = delta_y / delta_x
    origin = init_point
    return m, origin