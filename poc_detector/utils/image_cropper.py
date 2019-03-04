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
    working_dir = "/home/operador/Documentos/"
    image_filename = "crop_row_image_mask.JPG"
    image = cv2.imread( working_dir + image_filename)
    image_crops = image_cropper.process(image)
    index = 0
    for chunck in image_crops:
        image_title = "Image row: {}".format(index)

        #cv2.imshow(image_title, chunk)
        cv2.imwrite(working_dir + "_row_image_{}.jpeg".format(index), chunck )
        index = index +1

    cv2.waitKey(0)
    cv2.destroyAllWindows()



