import cv2
import numpy as np

from vector_utils import sort_y_axis
from vector_utils import get_middle_point
from vector_utils import is_valid_boundary_box

def get_countours(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blur = cv2.blur(gray, (3, 3))
    ret, thresh = cv2.threshold(blur, 50, 255, cv2.THRESH_BINARY)
    im2, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return contours

def get_convex_hull_boundary_box(contour):
    polyline = cv2.convexHull(contour, False)
    rect = cv2.minAreaRect(polyline)
    box = cv2.boxPoints(rect)
    box = np.intp(box)
    return box

def compute_aspect_ratio(box):
    dist_1 = np.linalg.norm(box[1] - box[0])
    dist_2 = np.linalg.norm(box[3] - box[2])
    largo_1 = np.linalg.norm(box[2] - box[0])
    largo_2 = np.linalg.norm(box[3] - box[1])
    validate_values_for_aspect_ratio_process(dist_1, largo_1)
    aspect_ratio = dist_1 / largo_1
    return aspect_ratio

def validate_values_for_aspect_ratio_process(width, height):
    if ((width == 0) | (height == 0)):
        raise ValueError('A very specific bad thing happened. Image or Heigth are Zero')

def compute_total_area_sum(contours):
    area_list = []
    for contour in contours:
        box = get_convex_hull_boundary_box(contour)
        area_countour = cv2.contourArea(box)
        area_list.append(float(area_countour))
    return np.sum(area_list)

def normalize_areas(area_list, area_sumatory):
    for index in xrange(len(area_list)):
        area_list[index] = area_list[index] * (1.0/ area_sumatory)
    return area_list

def is_valid_countour(contour,area_sumatory):
    area_countour = cv2.contourArea(contour) * (1.0 / area_sumatory)
    perimeter = cv2.arcLength(contour,True)
    is_valid = (area_countour > 0.02) & (area_countour < 0.25 ) & (perimeter < 250)
    return is_valid

def is_valid_aspect_ratio(box):
    result = False
    try:
        aspect_ratio = compute_aspect_ratio(box)
        result = (aspect_ratio > 0.2) & (aspect_ratio < 1.0)
    except Exception as e:
        pass
    return result

#TODO: Implement an Naive Bayesian Validator
def estimate_validation_of_countour(contour, area_sumatory, image_height):
    box = get_convex_hull_boundary_box(contour)
    is_valid_bb = is_valid_boundary_box(box,image_height,5 )
    is_aspect_ratio_valid = is_valid_aspect_ratio( box )
    is_countour_in_valid_range = is_valid_countour(contour, area_sumatory)
    is_valid =  is_countour_in_valid_range & is_valid_bb & is_aspect_ratio_valid
    return box, is_valid

def validate_point_in_valid_range(point_value, upper_value, lower_value):
    if(  point_value > upper_value):
            point_value = upper_value
    if ( point_value < lower_value):
        point_value =  lower_value
    return point_value
#Image_height = image.shape[0]
# image_width = image.shape[1]
def reorder_box_boundary(box, image_height, image_width):
    reorder_bb = []
    index  = 0
    for point in box:
        y_value = validate_point_in_valid_range(int(box[index][1]), image_height,0)
        x_value = validate_point_in_valid_range(int(box[index][0]), image_width,0)
        index += 1 
        reorder_bb.append((x_value, y_value))
    return reorder_bb

def compute_countours_from_image(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blur = cv2.blur(gray, (3, 3))
    ret, thresh = cv2.threshold(blur, 50, 255, cv2.THRESH_BINARY)
    _, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return contours, thresh