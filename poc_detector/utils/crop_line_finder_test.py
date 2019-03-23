import cv2
import matplotlib.pyplot as plt
from lane_finder import CropLaneFinder

if __name__ == "__main__":
    filename = "/home/operador/Documentos/crop_row_image_mask.JPG"
    print filename
    image = cv2.imread(filename)
    crop_lane_finder = CropLaneFinder()
    crop_lane_finder.find_lanes(image)
