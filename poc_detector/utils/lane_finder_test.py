import cv2
from lane_finder import LaneFinder

if __name__ == "__main__":
    lane_finder = LaneFinder()
    filename = "/home/operador/Documentos/_row_image_0.jpeg"
    print filename
    image = cv2.imread(filename)
    lane_finder.process_image(image)
    hull = lane_finder.hull_set
    for point in lane_finder.points_pair_set:
        cv2.line(image,(point[0] , point[1]),(point[2] , point[3]),(0,175,0),2)
    for i in range(len(hull)):
        color_contours = (0, 255, 0) # green - color for contours
        color = (0, 0, 255) # blue - color for convex hull
        # draw ith contour
        #cv2.drawContours(drawing, contours, i, color_contours, 1, 8, hierarchy)
        # draw ith convex hull object
        cv2.drawContours(image, hull, i, color, 1, 8)
    cv2.imshow('original',image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()