import numpy as np
import cv2
import matplotlib.pyplot as plt
import os
import ConfigParser


class SegmentorConfig():
    def __init__(self, config_filename='config.ini'):
        self.__config = ConfigParser.ConfigParser()
        self.__config.read(config_filename)
        self.__input_directories = None
        self.__output_directories = None
        self.__shadow_thershold = 0
        self.__create_output_dir = False
        self.__clean_output_dir = False

        self.__extract_config()
        self.__perform_operations()

    @property
    def input_dir(self):
        return self.__input_directories

    @property
    def output_dir(self):
        return self.__output_directories
    
    @property
    def shadow_threshold(self):
        return self.__shadow_thershold
    
    
    def __extract_config(self):
        directory_section = self.__config_section_map('directories', self.__config)
        self.__input_directories = directory_section['input_dir']
        self.__output_directories = directory_section['output_dir']
        #options
        options_section = self.__config_section_map('values', self.__config)
        self.__shadow_thershold = int(options_section['shadow_threshold'])
        self.__create_output_dir = options_section['shadow_threshold'] == 'true'
        self.__clean_output_directory = options_section['clean_output_directory'] == 'true'

    def __perform_operations(self):
        directory_exits =  os.path.exists(self.__output_directories)
        print "Creating output directory during config step"
        if (not os.path.exists(self.__output_directories)):
            os.makedirs(self.__output_directories)

        if self.__clean_output_dir and directory_exits:
            print "Cleaning Output directory during Config Step"
            for filename in os.listdir():
                os.unlink(filename)



    def __config_section_map(self, section, Config):
        dict1 = {}
        options = Config.options(section)
        for option in options:
            try:
                dict1[option] = Config.get(section, option)
                if dict1[option] == -1:
                    DebugPrint("skip: %s" % option)
            except:
                print("exception on %s!" % option)
                dict1[option] = None
        return dict1

class OtsuAdvance:
    def __init__(self, image=None, shadow_percentile=5):
        self.__image = image
        self.__percentile = shadow_percentile

    def compute_mask(self):
        image_hls = cv2.cvtColor(self.__image, cv2.COLOR_BGR2HLS)
        #print "Image shape: {}".format(image_hls.shape)
        hue, lightness, saturation = np.split(image_hls, 3 , axis=2)
        #print "Hue shape: {}".format(hue.shape)
        otsu_hue = cv2.threshold(hue, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        otsu_ligthness = cv2.threshold(lightness, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        otsu_saturation = cv2.threshold(saturation, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        otsu =  otsu_hue[1]
        #otsu = otsu_ligthness[1]
        #otsu = otsu_saturation[1]
        otsu_mask = otsu != 255
        #++++++++++++++++++++++++++++++++++++++++++++++++++
        image_lab = cv2.cvtColor(self.__image, cv2.COLOR_BGR2LAB)
        l_component, a_component, b_component = np.split(image_lab, 3 , axis=2)
        #print l_component.shape
        target_shape = (l_component.shape[0], l_component.shape[1])
        #print "Target Shape: {}".format(target_shape) 
        l_component = l_component.reshape(target_shape)
        shadow_threshold = np.percentile(l_component.ravel(),q=0)
        #for value in xrange(100):
        #    print "Percentile value: {}".format(np.percentile(l_component.ravel(),q=self.__percentile))
        #print "Shadow Percentile Value: {}".format(shadow_threshold)
        shadow_mask = l_component < shadow_threshold

        #++++++++++++++++++++++++++++++++++++++++++++++++++
        otsu_mask = otsu_mask | shadow_mask
        
        return otsu_mask

    def noise_reduction(self,image):
        return cv2.fastNlMeansDenoisingColored(image,None,10,10,7,21)


def show_mask(mask, image, title='', mask_color=(255, 0, 0)):
    display_image = image.copy()
    display_image[mask != 0] = mask_color
    plt.imshow(display_image)
    plt.title(title)
    plt.axis('off')
    plt.show()

def show_image(image, title=''):
    plt.imshow(image)
    plt.title(title)
    plt.axis('off')
    plt.show()

def save_masked_image(dirname, filename, image, mask, mask_color=(255, 255, 255)):
    image [mask!=0] = mask_color
    image[mask==0]=(0,0,0)
    cv2.imwrite(dirname + filename, image)

def process_directory(source_directory, target_directory, shadow_threshold=0):
    failling_to_process = 0
    process_files = 0
    for r, dirs, files in os.walk(source_directory):
        for file in files:
            if ".JPG" in file:
                image = cv2.imread(source_directory+file)
                
                otsu = OtsuAdvance(image, shadow_threshold)
                mask = None
                try:
                    mask = otsu.compute_mask()
                    process_files = process_files + 1
                except Exception as e:
                    print "Error Processing File----> : {}, Exception: {}".format(file, str(e))
                    failling_to_process =failling_to_process + 1
                else:
                    pass
                finally:
                    pass
                image_name = file.split('.')[0]
                save_masked_image(target_directory, image_name + "_mask.jpg", image, mask)
    print "Amount of Failled files to process: {}".format(failling_to_process)
    print "Amount of Succeded files to process: {}".format(process_files)


if __name__ == "__main__":
    config = SegmentorConfig()
    process_directory(config.input_dir, config.output_dir, config.shadow_threshold)
    #image = cv2.imread("/home/alrodriguez/Documents/CRBD/Images/crop_row_122.JPG")
    #otsu = OtsuAdvance(image,0)
    #mask = otsu.compute_mask()
    #show_mask(mask, image,"Otsu threshold")
    #show_image(image, 'raw image')
