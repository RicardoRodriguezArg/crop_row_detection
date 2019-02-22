import numpy as np
import cv2
import matplotlib as plt

class ImageLoader():
    def __init__(self, filename=None):
        self.__image = cv2.imread(filename, cv2.IMREAD_COLOR)
        self.__create_images_channel()

    @property
    def image(self):
        return self.__image

    def __create_images_channel(self):
        self.__blue_channel, self.__green_channel, self.__red_channel = cv2.split(self.__image)
