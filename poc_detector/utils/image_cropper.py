import numpy as np
import cv2

class ImageCropper():
    def __init__(self, region_count=4):
        self.__region_count = region_count
        

    def process(self, image):
        images_chuncks = []
        (h,w) = image.shape[:2]
        chunk_heigth = int(h/self.__region_count)
        initial_index = 0
        for index in xrange(self.__region_count):
            initial_index = chunk_heigth*index
            end_index = initial_index + chunk_heigth
            chunk = image[initial_index : end_index, :w]
            images_chuncks.append(chunk)
        return images_chuncks


if __name__ == "__main__":
    image_cropper = ImageCropper()
    image = cv2.imread("/home/operador/Documents/Proyects/crop_row_detection/poc_detector/utils/crop_row_image_example.jpeg")
    image_crops = image_cropper.process(image)
    index = 0
    for chunk in image_crops:
        image_title = "Image row: {}".format(index)

        cv2.imshow(image_title, chunk)
        index = index +1

    cv2.waitkey(0)



