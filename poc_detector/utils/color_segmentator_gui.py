import sys
from PyQt4.QtGui import *
from PyQt4 import QtGui
from PyQt4 import QtCore
from PyQt4.QtCore import *


class ColorSegmentatorGui(QtGui.QWidget):
    def __init__(self):
        super(ColorSegmentatorGui, self).__init__()
        self.__create_ui()

    def __create_ui(self):
        #general_layout
        hbox = QHBoxLayout()
        hbox = self.__create_right_panel(hbox)
        hbox = self.__create_left_panel(hbox)
        self.setLayout(hbox)
        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle('Color Segmentator Tool')    
        self.show()

    def __create_panels_layout(self):
        hbox = QHBoxLayout()

    def __create_right_panel(self, parent_layout):
        hbox =QVBoxLayout()
        image_label = QLabel()
        mask_label = QLabel()
        hbox.addWidget(image_label)
        hbox.addStretch(1)
        hbox.addWidget(mask_label)
        parent_layout.addLayout(hbox)
        return parent_layout


    def __create_left_panel(self, parent_layout):
        hbox =QVBoxLayout()
        #Configuration Grou
        group_configuration_Box = QGroupBox("Configuration Zone")
        vbox_configuration = QGridLayout()
        input_edit_line = QLineEdit("/Home")
        output_edit_line = QLineEdit("/Home")
        input_directory_label = QLabel("Input Directories")
        input_directory_label.setText("Input Directories:")
        output_directory_label = QLabel("Output Directories:")
        output_directory_label.setText("Output Directories")
        vbox_configuration.addWidget( input_directory_label,0,0 )
        vbox_configuration.addWidget( input_edit_line,0,1 )
        vbox_configuration.addWidget( input_edit_line,0,1 )
        vbox_configuration.addWidget( output_directory_label,1,0 )
        vbox_configuration.addWidget( output_edit_line ,1,1)
        group_configuration_Box.setLayout(vbox_configuration)

        groupBox = QGroupBox("Upper/Lower Values ")
        upper_lower = QLabel("Upper Range Values")
        h_upper_slider = QSlider(Qt.Horizontal)
        s_upper_slider = QSlider(Qt.Horizontal)
        v_upper_slider = QSlider(Qt.Horizontal)
        label_lower = QLabel("Lower Range Values")
        h_lower_slider = QSlider(Qt.Horizontal)
        s_lower_slider = QSlider(Qt.Horizontal)
        v_lower_slider = QSlider(Qt.Horizontal)

        
        h_upper_edit = QLineEdit("hupper")
        s_upper_edit = QLineEdit("supper")
        v_upper_edit = QLineEdit("vupper")
        
        h_lower_edit = QLineEdit("vlower")
        s_lower_edit = QLineEdit("vlower")
        v_lower_edit = QLineEdit("vlower")


        vbox = QGridLayout()

        vbox.addWidget(upper_lower,0,0)
        
        
        vbox.addWidget(h_upper_slider,1,0)
        vbox.addWidget(h_upper_edit,1,1)
        

        vbox.addWidget(s_upper_slider,2,0)
        vbox.addWidget(s_upper_edit,2,1)

        vbox.addWidget(v_upper_slider,3,0)
        vbox.addWidget(v_upper_edit,3,1)
        
        vbox.addWidget(label_lower,4,0)
        vbox.addWidget(h_lower_slider,5,0)
        vbox.addWidget(h_lower_edit,5,1)

        vbox.addWidget(s_lower_slider,6,0)
        vbox.addWidget(s_lower_edit,6,1)

        vbox.addWidget(v_lower_slider,7,0)
        vbox.addWidget(v_lower_edit,7,1)
        groupBox.setLayout(vbox)
        #end gorup definition
        hbox.addWidget(group_configuration_Box)
        hbox.addStretch(1)
        hbox.addWidget(groupBox)


        self.save_image_button = QPushButton("Save Image")
        self.next_image_button = QPushButton("Next Image")
        self.update_image_button = QPushButton("Update Image")
        hbox.addWidget(self.save_image_button)
        hbox.addStretch(1)
        hbox.addWidget(self.next_image_button)
        hbox.addStretch(1)
        hbox.addWidget(self.update_image_button)

        parent_layout.addLayout(hbox)
        return parent_layout



def main():
    app = QtGui.QApplication(sys.argv)
    ex = ColorSegmentatorGui()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()