import cv2
import matplotlib.pyplot as plt
from lane_finder import CropLaneFinder
import numpy as np

if __name__ == "__main__":
    filename = "/home/operador/Documentos/crop_row_image_mask.JPG"
    print filename
    image = cv2.imread(filename)
    crop_lane_finder = CropLaneFinder()
    crop_lane_finder.find_lanes(image)
    lines_per_column = crop_lane_finder.fusion_lines_data_point_per_bins()
    #print "Total of lines finds: {}".format(len(crop_lane_finder.total_lines_endpoints))
    print lines_per_column[0]
    pts = np.array([[lines_per_column[0][0][0],lines_per_column[0][0][1]],
    				[lines_per_column[0][0][2],lines_per_column[0][0][3]],
    				[lines_per_column[0][1][0],lines_per_column[0][1][1]],
    				[lines_per_column[0][1][2],lines_per_column[0][1][3]],
    				[lines_per_column[0][2][0],lines_per_column[0][2][1]],
    				[lines_per_column[0][2][2],lines_per_column[0][2][3]],
    				],			np.int32)
    pts = pts.reshape((-1,1,2))
    #cv2.polylines(image, pts, True, (0, 100, 20))
    #for lines in lines_per_column[3]:
    #	cv2.line(image,(lines[0] , lines[1]),(lines[2] , lines[3]),(0,0,100),2)

    for index in xrange(len(crop_lane_finder.total_lines_endpoints)):
    	for points_idx in xrange(len(crop_lane_finder.total_lines_endpoints[index])):
    		point = crop_lane_finder.total_lines_endpoints[index][points_idx]
    		cv2.line(image,(point[0] , point[1]),(point[2] , point[3]),(0,175,0),2)
    		cv2.circle(image,(point[2] , point[3]), 2, (255,0,255), -1)

    for lines in lines_per_column[3]:
    	cv2.line(image,(lines[0] , lines[1]),(lines[2] , lines[3]),(0,0,100),2)
    	#for point in crop_lane_finder.total_lines_endpoints[0]:
    	#	print "Index: {}".format(index)
    	#	point = crop_lane_finder.total_lines_endpoints[index][0]
    	#	cv2.line(image,(point[0] , point[1]),(point[2] , point[3]),(0,175,0),2)
    #print crop_lane_finder.x_points
    #print crop_lane_finder.y_points
    #cv2.polylines(img, np.int32([points]), 1, (255,255,255))
    cv2.imshow('original',image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
