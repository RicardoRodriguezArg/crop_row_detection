import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

class GrpahCut():
    def __init__(self, matrix_shape=(1,65),roi=(30,30, 300, 500)):
        self.__mask= None
        self.clear(matrix_shape)
        self.__roi = roi
    
    def clear(self, matrix_shape=(1,65)):
        self.__mask= None
        self.__background_model = np.zeros(matrix_shape, np.float)
        self.__foreground_model = np.zeros(matrix_shape, np.float)

    def __create_mask_array(self, image):
        return np.zeros(image.shape[:2],dtype=np.uint8)

    def graph_cut(self, filename, roi=(30, 30, 277, 165)):
        image = self.__load_image(filename)
        mask = self.__create_mask_array(image)
        cv2.grabCut(image, mask, roi, self.__background_model, self.__foreground_model, 5, cv2.GC_INIT_WITH_RECT)
        new_mask = self.__process_mask(mask)
        image = self.__reprocess(image, new_mask)
        self.__plot_image(image)


    def __plot_image(self, image):
        plt.imshow(image)
        plt.colorbar()
        plt.show()


    def __process_mask(self, mask):
        mask = np.where((mask==0) | (mask==2), 0, 1).astype('uint8')
        return mask

    def __reprocess(self, image, new_mask):
        return image * new_mask[:,:,np.newaxis]

    def __load_image(self, filename):
        return cv2.imread(filename)

    def interactive_graph_cut(self, image_filename, mask_image_filename=None):
        image = cv2.imread(image_filename)
        mask = self.__create_mask_array(image)
        newmask = cv2.imread(mask_image_filename, 0)
        matrix_shape = (1,65)
        self.__background_model = np.zeros(matrix_shape, np.float)
        self.__foreground_model = np.zeros(matrix_shape, np.float)
        mask[ newmask == 0 ] = 1
        mask[ newmask == 255 ] = 0
        mask, self.__background_model, self.__foreground_model = cv2.grabCut(image, mask, None,
                                                                                    self.__background_model,
                                                                                    self.__foreground_model,
                                                                                    10, cv2.GC_INIT_WITH_MASK)
        mask = self.__process_mask(mask)
        image = self.__reprocess(image, mask)

        return image


def save_masked_image(dirname, filename, image):
    cv2.imwrite(dirname + filename, image)

def process_directory(graph_cut_process, source_directory, target_directory, filename_mask):
    failling_to_process = 0
    process_files = 0
    graph_cut_process.clear()
    for r, dirs, files in os.walk(source_directory):
        for file in files:
            if ".JPG" in file:
                try:
                    image_name = file.split('.')[0]
                    target_file_name = image_name + "_mask_extended.jpg"
                    print "Image to process: {}".format(source_directory + file)
                    image = graph_cut.interactive_graph_cut( source_directory + file, filename_mask)
                    graph_cut.clear()
                    save_masked_image(target_directory, target_file_name, image )
                except Exception as e:
                    print "Error Processing File----> : {}, Exception: {}".format(file, str(e))
                    failling_to_process =failling_to_process + 1
                else:
                    pass
                finally:
                    pass
                
    print "Amount of Failled files to process: {}".format(failling_to_process)
    print "Amount of Succeded files to process: {}".format(process_files)

if __name__ == '__main__':
    graph_cut = GrpahCut()
    source_directory = "/home/alrodriguez/Documents/CRBD/Images/"
    target_directory = "/home/alrodriguez/Documents/CRBD/images_mask_3/"
    filename_mask = "/home/alrodriguez/Documents/CRBD/Images_mask/crop_row_001_mask.jpg"
    #image_filename = "/home/alrodriguez/Documents/CRBD/Images/crop_row_005.JPG"
    process_directory(graph_cut, source_directory, target_directory, filename_mask)
    #graph_cut.graph_cut(image_filename)



