import numpy as np
import cv2
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import colors
from matplotlib import cm
import os
import sys
#from PyQt5.QtWidgets import QApplication, QPushButton
from PyQt4.QtGui import *
from PyQt4 import QtGui
from PyQt4 import QtCore
from PyQt4.QtCore import *

class SegmetationByColor():
    def __init__(self, target_directory=None):
        self.__target_directory = target_directory

    def process(self,working_path, name, target_path):
        print "Filename: {}".format(working_path + name)
        image = cv2.imread(working_path + name)
        #image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(hsv)
        l_green = np.uint8([[[62, 107, 88]]])
        h_green = np.uint8([[[89, 128, 120]]])
        l_hsv = cv2.cvtColor(l_green,cv2.COLOR_BGR2HSV)
        h_hsv =  cv2.cvtColor(h_green,cv2.COLOR_BGR2HSV)
        
        #hsv_green = cv2.cvtColor(green,cv2.COLOR_BGR2HSV)
        #Codigo para plotear
        '''
        figure = plt.figure()
        axis = figure.add_subplot(1,1,1,projection="3d")
        pixel_colors = image.reshape((np.shape(image)[0]*np.shape(image)[1], 3))
        norm = colors.Normalize(vmin=-1.,vmax=1.)
        norm.autoscale(pixel_colors)
        pixel_colors = norm(pixel_colors).tolist()
        axis.scatter(h.flatten(),s.flatten(), v.flatten(), facecolors=pixel_colors, marker=".")
        axis.set_xlabel("Hue")
        axis.set_ylabel("Saturation")
        axis.set_zlabel("Value")
        plt.show()
        '''
        #mask = cv2.inRange(hsv, (22,64  ,60), (182,255, 255))
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,90, 225))# crop_row_081
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,75, 225))# crop_row_082
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,88, 225))# crop_row_083
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,85, 225))# crop_row_084
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,75, 225))# crop_row_085
        #mask = cv2.inRange(hsv, (16,23  ,130), (45,95, 225))# crop_row_086
        #mask = cv2.inRange(hsv, (44,23  ,130), (100,255, 225))# crop_row_001
        #mask = cv2.inRange(hsv, (40, 60  ,60), (185, 255, 225))# crop_row_002
        #mask = cv2.inRange(hsv, (30, 60  ,145), (45, 105, 225))# crop_row_003
        #mask = cv2.inRange(hsv, (30, 60  ,145), (45, 105, 225))# crop_row_005 # crop_row_006
        #mask = cv2.inRange(hsv, (30, 85  ,105), (220, 225, 225))# crop_row_008 # crop_row_007
        #mask = cv2.inRange(hsv, (30, 75  ,55), (220, 225, 225))# crop_row_009
        #mask = cv2.inRange(hsv, (30, 75  ,40), (220, 225, 225))# crop_row_010, 11, 12, 13,
        #mask = cv2.inRange(hsv, (40, 75  ,40), (220, 225, 225))# 14
        #mask = cv2.inRange(hsv, (40, 75  ,40), (220, 225, 225))# 15, 16
        #mask = cv2.inRange(hsv, (33, 75  ,75), (220, 225, 225))# 17, 18
        #mask = cv2.inRange(hsv, (28, 20  ,75), (220, 225, 225))# 19
        #mask = cv2.inRange(hsv, (25, 20  ,75), (220, 225, 225))# 20, 21
        #mask = cv2.inRange(hsv, (35, 20  ,75), (220, 225, 225))# 22, 23
        #mask = cv2.inRange(hsv, (30, 95  ,115), (220, 225, 225))# 24, 25, 26
        #mask = cv2.inRange(hsv, (30, 110  ,105), (220, 225, 225))# 27
        #mask = cv2.inRange(hsv, (35, 105  ,105), (220, 225, 225))# 28, 29, 30
        #mask = cv2.inRange(hsv, (35, 95  ,105), (220, 225, 225))# 31, 32, 33, 34
        #mask = cv2.inRange(hsv, (40, 75  ,105), (220, 225, 225))# 35, 36, 37
        #mask = cv2.inRange(hsv, (40, 100  ,95), (60, 225, 225))# 38, 39, 40
        #mask = cv2.inRange(hsv, (25, 87, 45), (160, 225, 225))# 41, 42
        #mask = cv2.inRange(hsv, (25, 85, 85), (160, 225, 225))# 43, 44
        #mask = cv2.inRange(hsv, (30, 90, 80), (160, 225, 225))# 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,57 
        #mask = cv2.inRange(hsv, (20, 110, 100), (160, 225, 225))# 58, 59, 60, 61
        #mask = cv2.inRange(hsv, (35, 100, 70), (160, 225, 225))# 62
        #mask = cv2.inRange(hsv, (35, 100, 70), (160, 225, 225))# 63, 64, 65, 66, 67
        mask = cv2.inRange(hsv, (35, 100, 70), (160, 225, 225))# 65
        res = cv2.bitwise_and(image,image, mask=mask)
        cv2.imshow('mask',mask)
        cv2.imshow('image',image)
        cv2.imshow('result',res)
        
        cv2.waitKey(0)
        cv2.destroyAllWindows() 
        name = name.split('.')[0] + '_mask.JPG'
        self.save_image(target_path + name, mask)
        #result = cv2.bitwise_and(hsv, hsv, mask=mask)
        
    def save_image(self,filename, image):
        cv2.imwrite(filename, image)

if __name__ == "__main__":
    working_path = "/home/alrodriguez/Documents/CRBD/Images/"
    target_path = "/home/alrodriguez/Documents/CRBD/images_mask_3/"
    name = "crop_row_067.JPG"
    
    app = QApplication([])
    widget = QWidget()
   

    widget.resize(600, 800)
    widget.setWindowTitle("Color Range Segmentator")
    HBoxlayout  = QtGui.QHBoxLayout(widget)
    #Rigth Side
    VBoxlayout  = QtGui.QVBoxLayout()
    image = QPixmap(working_path + name)
    image_label = QLabel(widget)
    image_label.setPixmap(image)
    
    mask_label = QLabel(widget)
    VBoxlayout.addWidget(image_label)
    VBoxlayout.addWidget(mask_label)
    
    #left side config
    
    #Upper Values
    left_layout = QtGui.QVBoxLayout()
    upper_group_layout = QtGui.QVBoxLayout()
    upper_value_h = QSlider(Qt.Horizontal)
    upper_value_s = QSlider(Qt.Horizontal)
    upper_value_v = QSlider(Qt.Horizontal)
    left_layout.addWidget(upper_value_h)
    left_layout.addWidget(upper_value_s)
    left_layout.addWidget(upper_value_v)

    lower_group_layout = QtGui.QVBoxLayout()
    lower_value_h = QSlider(Qt.Horizontal)
    lower_value_s = QSlider(Qt.Horizontal)
    lower_value_v = QSlider(Qt.Horizontal)
    left_layout.addWidget(lower_value_h)
    left_layout.addWidget(lower_value_s)
    left_layout.addWidget(lower_value_v)
    #buttoms config
    update_bottom = QPushButton("Update Image")
    save_bottom = QPushButton("Save Image")
    Next_bottom = QPushButton("Next Image")

    left_layout.addWidget(update_bottom)
    left_layout.addWidget(save_bottom)
    left_layout.addWidget(Next_bottom)

    #values_slider_group.setLayout(left_layout)
    VBoxlayout.setLayout(left_layout)
    
    
    HBoxlayout.setLayout(VBoxlayout)

    


    widget.setLayout(HBoxlayout)

    widget.resize(image.width(), image.height())
    widget.show()
    sys.exit(app.exec_())
    #color_segmentator = SegmetationByColor()
    #name = "/home/alrodriguez/Documents/test/test_1.jpg"
    #color_segmentator.process(working_path, name, target_path)
    #image = cv2.imread("/home/alrodriguez/Documents/CRBD/Images/crop_row_001.JPG")
    #print "Name: {}".format(name)
    #hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    #mask = cv2.inRange(hsv, (112,97,60), (133,29,60) )
    #cv2.imshow('name',mask)
    #cv2.waitKey(0)
    #cv2.destroyAllWindows()