import cv2
from processing_segmented_image_utils import *
from splines_builder import Spline

from image_cropper import ImageCropper

class LaneFinder():
    def __init__(self):
        self.__hulls_set = list()
        self.__x_point_set = list()
        self.__y_point_set = list()
        self.__points_pair_set = list()

    def reset(self):
        self.__hulls_set = list()
        self.__x_point_set = list()
        self.__y_point_set = list()
        self.__points_pair_set = list()


    def process_image(self, image):
        contours, _ = compute_countours_from_image(image)
        area_sumatory = compute_total_area_sum(contours)
        for contour in contours:
            box, is_valid = estimate_validation_of_countour(contour, area_sumatory, image.shape[0])
            if is_valid:
                polyline = cv2.convexHull(contour, False)
                self.__hulls_set.append(polyline)
                points = reorder_box_boundary(box, image.shape[0], image.shape[1])
                points = sort_y_axis(points)
                first_set = [points[0], points[1]]
                second_set =  [points[2], points[3]]
                delta_x_1, _ = get_middle_point(first_set)
                delta_x_2, _ = get_middle_point(second_set)
                point_x_1 = points[0][0] + delta_x_1
                point_y_1 = 0
                self.__x_point_set.append(point_x_1)
                self.__y_point_set.append(point_y_1)
                point_x_2 = points[2][0] + delta_x_2
                point_y_2 = image.shape[0]
                self.__x_point_set.append(point_x_2)
                self.__y_point_set.append(point_y_2)
                self.__points_pair_set.append((point_x_1, point_y_1, point_x_2, point_y_2))
                

    @property
    def hull_set(self):
        return self.__hulls_set

    @property
    def x_points(self):
        return self.__x_point_set

    @property
    def y_points(self):
        return self.__y_point_set

    @property
    def points_pair_set(self):
        return self.__points_pair_set


class CropLaneFinder():
    def __init__(self, image_chunck_count=4):
        self.__image_chunck_count = image_chunck_count
        self.__x_points = list()
        self.__y_points = list()
        self.__splines_stimator = Spline()

    def find_lanes(self, image):
        """
        Input Image is already Segmentated
        """
        image_cropper = ImageCropper(self.__image_chunck_count)
        image_chunks = image_cropper.process(image)
        lane_finder = LaneFinder()
        for image_chunck in image_chunks:
            lane_finder.process_image(image_chunck)
            self.__x_points.extend(lane_finder.x_points)
            self.__y_points.extend(lane_finder.y_points)
            lane_finder.reset()
        self.__splines_stimator.process_points(np.array(sorted(self.__x_points)), np.array(self.__y_points))

    @property
    def splines_stimator(self):
        return self.__splines_stimator
    


