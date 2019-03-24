import cv2
from processing_segmented_image_utils import *
from splines_builder import Spline
from image_cropper import ImageCropper
from line_points_graph import LinePointsGraph

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

    def __process_finals_points(self, point_1_x, point_1_y, point_2_x, point_2_y):
        if (point_1_y > point_2_y):
            temp_x = point_1_x
            temp_y = point_1_y
            point_1_x = point_2_x
            point_1_y = point_2_y
            point_2_x = temp_x 
            point_2_y = temp_y
        return point_1_x, point_1_y, point_2_x, point_2_y


    def process_image(self, image, delta_y=0):
        contours, _ = compute_countours_from_image(image)
        area_sumatory = compute_total_area_sum(contours)
        for contour in contours:
            box, is_valid = estimate_validation_of_countour(contour, area_sumatory, image.shape[0])
            if is_valid:
                polyline = cv2.convexHull(contour, False)
                print len(polyline)
                self.__hulls_set.append(polyline)
                points = reorder_box_boundary(box, image.shape[0], image.shape[1])
                points = sort_y_axis(points)
                first_set = [points[0], points[1]]
                second_set =  [points[2], points[3]]
                delta_x_1, _ = get_middle_point(first_set)
                delta_x_2, _ = get_middle_point(second_set)
                point_x_1 = points[0][0] + delta_x_1
                point_y_1 = 0 + delta_y
                self.__x_point_set.append(point_x_1)
                self.__y_point_set.append(point_y_1)
                point_x_2 = points[2][0] + delta_x_2
                point_y_2 = image.shape[0] + delta_y
                self.__x_point_set.append(point_x_2)
                self.__y_point_set.append(point_y_2)
                point_x_1, point_y_1, point_x_2, point_y_2 = self.__process_finals_points(point_x_1, point_y_1, point_x_2, point_y_2)
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

    def update_y_origin(self, origin_value):
        for index in xrange(len(self.__y_point_set)):
            self.__y_point_set[index] = self.__y_point_set[index] + origin_value

class CropLaneFinder():
    def __init__(self, image_chunck_count=4):
        self.__image_chunck_count = image_chunck_count
        self.__x_points = list()
        self.__y_points = list()
        self.__points_pair_set = list()        
        self.__splines_stimator = Spline()

    def find_lanes(self, image):
        """
        Input Image is already Segmentated
        """
        image_cropper = ImageCropper(self.__image_chunck_count)
        image_chunks = image_cropper.process(image)
        lane_finder = LaneFinder()
        frame_image_height = image_cropper.frame_image_height
        frame_chunck_count = 0
        for image_chunck in image_chunks:
            #It is processing from lower part of the image to upper
            lane_finder.process_image(image_chunck, frame_image_height * frame_chunck_count)
            self.__points_pair_set.append(lane_finder.points_pair_set)
            frame_chunck_count += 1
            self.__y_points.extend(lane_finder.y_points)
            lane_finder.reset()
        #self.__splines_stimator.process_points(np.array(sorted(self.__x_points)), np.array(self.__y_points))

    @property
    def splines_stimator(self):
        return self.__splines_stimator
    
    @property
    def x_points(self):
        return self.__x_points

    @property
    def y_points(self):
        return self.__y_points
    
    @property
    def total_lines_endpoints(self):
        return self.__points_pair_set

    def transform_idx_to_points(self, data_idx_points):
        data_points = list()
        for point_dupla in data_idx_points:
            point = self.total_lines_endpoints[point_dupla[0]][point_dupla[1]]
            data_points.append(point)
        return data_points



    def fusion_lines_data_point_per_bins(self):
        """
        It must return a complete crop row set of o
        """
        points_graph = LinePointsGraph()
        for image_row_index in xrange(len(self.total_lines_endpoints)-1):
            for line_index in xrange(len(self.total_lines_endpoints[image_row_index])):
                current_line = self.total_lines_endpoints[image_row_index][line_index]
                smaller_dist = 10000
                selected_index = -1
                for next_line_index in xrange(len(self.total_lines_endpoints[image_row_index + 1 ])):
                    next_line = self.total_lines_endpoints[image_row_index + 1][next_line_index]
                    first_point = np.array([current_line[2], current_line[3]])
                    second_point = np.array([next_line[0], next_line[1]])
                    distance_from_point_to_point = np.linalg.norm(first_point - second_point)
                    if (distance_from_point_to_point < smaller_dist) & (distance_from_point_to_point < 10):
                        smaller_dist = distance_from_point_to_point
                        selected_index = next_line_index
                    #print "Row: {} Line ID: {}".format(image_row_index, line_index)
                    #print "Comparing With: {} Next Line Index: {}".format(image_row_index + 1 ,next_line_index )
                    #print "delta Y {}".format(current_line[3] - next_line[1])
                    #print "Distance: {}".format(distance_from_point_to_point)
                if selected_index != -1:
                   #print "Frame ID : {} ID {} ->Next Frame ID: {} Next Id {}".format(image_row_index, line_index, image_row_index + 1,selected_index)
                   points_graph.add_edge(image_row_index, line_index, image_row_index + 1,selected_index)
                else:
                    #print "Lonley Vertex: Frame ID : {} ID {} ".format(image_row_index, line_index)
                    points_graph.add_point(image_row_index, line_index)

                #print "======================"
            #print "RRRRRRRRRRRRRRRRRRRRRRRRRR"
        
        lines_per_colum = list()
        for image_row_index in xrange(len(self.total_lines_endpoints)):
            for line_index in xrange(len(self.total_lines_endpoints[image_row_index])):
                point_set = points_graph.get_list_of_points(image_row_index, line_index)
                if (len(point_set)>0):
                    lines_per_colum.append(self.transform_idx_to_points(point_set))
        return lines_per_colum