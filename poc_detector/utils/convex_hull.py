import cv2
import numpy as np

from vector_utils import sort_y_axis
from vector_utils import get_middle_point
from vector_utils import is_valid_boundary_box

def sortSecond(val):
    return val[1]

def alternative_process(points):
    while(points[0][1] > 10) | (points[1][1] > 10):
        points = rotate(points, -1)

    return points



def sort_all_points(vector_points):
    index = 0
    total_size = len(vector_points)
    while (index < total_size ):
        vector_points = sort_points(vector_points, index , index + 1)
        index = index + 2
    return vector_points


if __name__ == "__main__":
    filename = "/home/operador/Documentos/_row_image_1.jpeg"
    print filename
    image = cv2.imread(filename)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blur = cv2.blur(gray, (3, 3))
    ret, thresh = cv2.threshold(blur, 50, 255, cv2.THRESH_BINARY)
    im2, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    print "Image Dimension: {}".format(image.shape)
    image_area = image.shape[0] * image.shape[1]
    print "Area de la imagen: {}".format(image.shape[0] * image.shape[1])
    hull = []
    # calculate points for each contour
    area_list = []
    polyline_lenght_list = []
    index = 0
    for contour in contours:
        # creating convex hull object for each contour
        polyline = cv2.convexHull(contour, False)
        rect = cv2.minAreaRect(polyline)
        box = cv2.boxPoints(rect)
        box = np.int0(box)

        area_countour = cv2.contourArea(box)
        #print "Porcentaje Area: {}".format((area_countour * 100.0) / image_area)
        area_list.append(float(area_countour))
        #print "Non-Selected Index: {} Area:{}".format(index, area_countour)
        index = index + 1
        #if ( (polyline_length > 4) & (polyline_length < 20) & (area_countour >900 ) & (area_countour <3000 )):
        #if ( (polyline_length > 6) & (polyline_length < 10) ):
        #    print "----->>>> Selected Len: {}   Area:{}".format(len(polyline), area_countour)
        #hull.append(polyline)
    area_sumatory = np.sum(area_list)
    polyline_sumatory = np.sum(polyline_lenght_list)
    
    for index in xrange(len(area_list)):
        area_list[index] = area_list[index] * (1.0/ area_sumatory)
        #print "Index: {}  Area Normalizada: {}".format(index, area_list[index])

    area_std_deviation = np.std(area_list)
    area_mean = np.mean(area_list)
    
    print "====================================================="
    print "MEdiana Area: {}".format(np.percentile(area_list, 50))
    
    print "Standar Deviation Area: {}".format(np.std(area_list))
    
    print "Mean Area: {}".format(np.mean(area_list))
    
    print "====================================================="
    index = 0
    drawing = np.zeros((thresh.shape[0], thresh.shape[1], 3), np.uint8)
    rows,cols = drawing.shape[:2]
    delta = 50

    for contour in contours:
        value = 0
        # creating convex hull object for each contour
        polyline = cv2.convexHull(contour, False)
        polyline_length = len(polyline)
        area_countour = cv2.contourArea(contour) * (1.0 / area_sumatory)
        #print "Area Normalizada: {} Index: {}".format(area_countour, index)
        perimeter = cv2.arcLength(contour,True)
        if (area_countour > 0.02) & (area_countour < 0.25 ) & (perimeter < 250):
        #if (area_countour > 0.02) & (area_countour < 0.125 ):
            
            rect = cv2.minAreaRect(polyline)
            box = cv2.boxPoints(rect)
            box = np.intp(box)
            dist_1 = np.linalg.norm(box[1] - box[0])
            dist_2 = np.linalg.norm(box[3] - box[2])
            largo_1 = np.linalg.norm(box[2] - box[0])
            largo_2 = np.linalg.norm(box[3] - box[1])
            aspect_ratio = dist_1 / largo_1
            #print "---> Index: {}".format(index)
            #print "---> Ancho 1: {} Ancho 2: {}".format(dist_1, dist_2)
            #print "---> LArgo 1: {} Largo 2: {}".format(largo_1, largo_2)
            #print "Perimenter: {}".format(perimeter)
            is_valid_bb = is_valid_boundary_box(box,image.shape[0],5 )

            if (aspect_ratio > 0.2) & (aspect_ratio < 1.0) & (is_valid_bb):
            #if (aspect_ratio > 0.2) & (aspect_ratio < 1.0):
                #print "Area Seleccionada: {}".format(area_countour)
                #print "-----------------"
                #print "Index: {}".format(index)
                #print "Ancho 1: {} Ancho 2: {}".format(dist_1, dist_2)
                #print "LArgo 1: {} Largo 2: {}".format(largo_1, largo_2)
                #print "Aspect Ration: {}".format(aspect_ratio)
                #print "-----------------"
                
                hull.append(polyline)
                points = []
                print "box 0 {}".format(box[0])
                print "box 1 {}".format(box[1])
                print "box 2 {}".format(box[2])
                print "box 3 {}".format(box[3])
                
                y0_value = int(box[0][1])
                x0_value = int(box[0][0])
                if( y0_value > image.shape[0]):
                    y0_value = image.shape[0]
                if( x0_value > image.shape[1]):
                    x0_value = image.shape[1]
                points.append((x0_value, y0_value))
                print "y0 value: {}".format(y0_value)
                print "x0 value: {}".format(x0_value)
                
                y1_value = int(box[1][1])
                x1_value = int(box[1][0])
                if( y1_value > image.shape[0]):
                    y1_value = image.shape[0]
                elif y1_value< 0:
                    y1_value = 0

                if( x1_value > image.shape[1]):
                    x1_value = image.shape[1]
                elif x1_value< 0:
                    x1_value = 0
                print "y1 value: {}".format(y1_value)
                print "x1 value: {}".format(x1_value)
                points.append((x1_value, y1_value))
                
                y2_value = int(box[2][1])
                x2_value = int(box[2][0])
                if y2_value > image.shape[0]:
                    y2_value = image.shape[0]
                elif y2_value< 0:
                    y2_value = 0
                if x2_value > image.shape[1]:
                    x2_value = image.shape[1]
                elif x2_value < 0:
                    x2_value = 0
                print "y2 value: {}".format(y2_value)
                print "x2 value: {}".format(x2_value)
                points.append((x2_value, y2_value))
                
                y3_value = int(box[3][1])
                x3_value = int(box[3][0])
                if y3_value > image.shape[0]:
                    y3_value = image.shape[0]
                elif y3_value< 0:
                    y3_value = 0
                if x3_value > image.shape[1]:
                    x3_value = image.shape[1]
                elif x3_value < 0:
                    x3_value = 0
                print "y3 value: {}".format(y3_value)
                print "x3 value: {}".format(x3_value)
                points.append((x3_value, y3_value))
                
                print points
                points = sort_y_axis(points)
                print points
                x0_value = points[0][0]
                y0_value = points[0][1]
                x1_value = points[1][0]
                y1_value = points[1][1]
                x2_value = points[2][0]
                y2_value = points[2][1]
                x3_value = points[3][0]
                y3_value = points[3][1]
                #New Method
                first_set = [points[0], points[1]]
                second_set =  [points[2], points[3]]
                
                delta_x_1, delta_y_1 = get_middle_point(first_set)
                delta_x_2, _ = get_middle_point(second_set)

                point_x_1 = x0_value + delta_x_1
                point_y_1 = 0
                point_x_2 = x2_value + delta_x_2
                point_y_2 = image.shape[0]


               
                print "Index: {}".format(index)
                print "Puntos Medios: X_1: {} Y_1 {}".format(point_x_1, point_y_1)
                print "Puntos Medios: X_2: {} Y_2 {}".format(point_x_2, point_y_2)
                print "Modified Middle point: {}".format(get_middle_point(first_set))

                cv2.circle(drawing,(x0_value, y0_value), 2, (255,255,255), -1)
                cv2.circle(drawing,(x1_value, y1_value), 2, (255,255,255), -1)
                cv2.circle(drawing,(x2_value, y2_value), 2, (0,100,0), -1)
                cv2.circle(drawing,(x3_value, y3_value), 2, (0,100,0), -1)

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