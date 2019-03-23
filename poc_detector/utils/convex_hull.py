import cv2
from processing_segmented_image_utils import *

if __name__ == "__main__":
    filename = "/home/operador/Documentos/_row_image_1.jpeg"
    print filename
    image = cv2.imread(filename)
    contours, thresh = compute_countours_from_image(image)
    hull = []
    # calculate points for each contour
    polyline_lenght_list = []
    index = 0

    drawing = np.zeros((thresh.shape[0], thresh.shape[1], 3), np.uint8)
    area_sumatory = compute_total_area_sum(contours)
    for contour in contours:
        box, is_valid = estimate_validation_of_countour(contour, area_sumatory, image.shape[0])
        if is_valid:
            polyline = cv2.convexHull(contour, False)    
            hull.append(polyline)

            points = reorder_box_boundary(box, image.shape[0], image.shape[1])
            points = sort_y_axis(points)
            #x0_value = points[0][0]
            #y0_value = points[0][1]
            #x1_value = points[1][0]
            #y1_value = points[1][1]
            #x2_value = points[2][0]
            #y2_value = points[2][1]
            #x3_value = points[3][0]
            #y3_value = points[3][1]
            #New Method
            first_set = [points[0], points[1]]
            second_set =  [points[2], points[3]]
            
            delta_x_1, _ = get_middle_point(first_set)
            delta_x_2, _ = get_middle_point(second_set)

            point_x_1 = points[0][0] + delta_x_1
            point_y_1 = 0
            point_x_2 = points[2][0] + delta_x_2
            point_y_2 = image.shape[0]


           
            print "Index: {}".format(index)
            print "Puntos Medios: X_1: {} Y_1 {}".format(point_x_1, point_y_1)
            print "Puntos Medios: X_2: {} Y_2 {}".format(point_x_2, point_y_2)
            print "Modified Middle point: {}".format(get_middle_point(first_set))

            #cv2.circle(drawing,(x0_value, y0_value), 2, (255,255,255), -1)
            #cv2.circle(drawing,(x1_value, y1_value), 2, (255,255,255), -1)
            #cv2.circle(drawing,(x2_value, y2_value), 2, (0,100,0), -1)
            #cv2.circle(drawing,(x3_value, y3_value), 2, (0,100,0), -1)

            cv2.circle(drawing,(point_x_1 , point_y_1), 2, (255,0,255), -1)
            cv2.circle(drawing,(point_x_2 , point_y_2), 2, (255,255,0), -1)
            # Draw a diagonal blue line with thickness of 5 px
            cv2.line(image,(point_x_1 , point_y_1),(point_x_2 , point_y_2),(0,175,0),2)
                
                
                #cv2.circle(drawing,(x3_value , y3_value), 5, (0,122,100), -1)
                
        index = index + 1
        print"====================================="

    
    for i in range(len(hull)):
        color_contours = (0, 255, 0) # green - color for contours
        color = (0, 0, 255) # blue - color for convex hull
        # draw ith contour
        #cv2.drawContours(drawing, contours, i, color_contours, 1, 8, hierarchy)
        # draw ith convex hull object
        cv2.drawContours(drawing, hull, i, color, 1, 8)
    cv2.imshow('original',image)
    cv2.imshow('result',drawing)
    cv2.waitKey(0)
    cv2.destroyAllWindows()