#FROM ubuntu:latest
FROM nvidia/cuda:9.1-devel
#install Opencv Dependencies
RUN apt-get update
#cmake for c++17

RUN apt-get update
RUN apt-get install gcc-9 g++-9

RUN apt-get install apt-transport-https ca-certificates gnupg software-properties-common wget -y
RUN add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
RUN apt update
RUN apt install python3-dev python3-numpy -y
RUN apt install git build-essential cmake unzip pkg-config -y
RUN apt install libjpeg-dev libpng-dev libtiff-dev libjasper-dev libjasper1 libavcodec-dev libavformat-dev libswscale-dev -y
RUN apt install libv4l-dev libxvidcore-dev libx264-dev libgtk-3-dev -y
RUN apt install libatlas-base-dev gfortran -y
RUN apt install libtbb2 libtbb-dev -y
RUN apt install openexr -y

RUN mkdir Documents
WORKDIR Documents

#install cmake 3.17
RUN wget https://cmake.org/files/v3.16/cmake-3.16.0-Linux-x86_64.sh
RUN chmod +x ./cmake-3.16.0-Linux-x86_64.sh
RUN mkdir -p /opt/cmake
RUN ./cmake-3.16.0-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/bin/cmake
#Installing GFlags
WORKDIR /home/Documents
RUN git clone https://github.com/gflags/gflags.git
RUN cd gflags && mkdir build && cd build && cmake .. -DBUILD_SHARED_LIBS=ON && make && make install && ldconfig

#opencv
RUN git clone https://github.com/opencv/opencv.git
RUN git clone https://github.com/opencv/opencv_contrib.git

RUN wget https://bootstrap.pypa.io/get-pip.py
RUN python3 get-pip.py
RUN pip install numpy
RUN cd opencv && mkdir build&& cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D WITH_CUDA=OFF \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D BUILD_EXAMPLES=ON .. && make && make install && ldconfig

#install Ceres
WORKDIR /home/Documents
RUN apt-get install libflann-dev libboost-all-dev libeigen3-dev libsuitesparse-dev libgoogle-glog-dev -y
RUN git clone https://ceres-solver.googlesource.com/ceres-solver
WORKDIR ceres-solver
RUN mkdir build && cd build && cmake .. && make && make install
#install eigen
WORKDIR /home/Documents
#RUN git clone https://github.com/eigenteam/eigen-git-mirror.git
#RUN cd eigen-git-mirror && mkdir build && cd build & cmake .. && make && make install
#install VTK

RUN wget http://www.vtk.org/files/release/7.1/VTK-7.1.0.tar.gz
RUN apt-get install vim freeglut3-dev libgtest-dev -y
RUN tar -xf VTK-7.1.0.tar.gz
RUN cd VTK-7.1.0 && mkdir build && cd build && cmake .. && make && make install
#install PCL
WORKDIR /home/Documents
RUN git clone https://github.com/PointCloudLibrary/pcl.git
RUN cd pcl && mkdir build && cd build && cmake .. && make && make install

#
WORKDIR /home/Documents
#ADD . ./modules
#VOLUME ./modules
#test data
RUN git clone https://github.com/OpenDroneMap/odm_data_aukerman.git
#install PDAL
RUN add-apt-repository ppa:ubuntugis/ppa -y && apt-get update
RUN apt-get install libgdal-dev gdal-bin libjsoncpp-dev -y
RUN git clone https://github.com/PDAL/PDAL.git
RUN cd PDAL && mkdir build && cd build && cmake .. && make && make install
WORKDIR /home/Documents
RUN git clone https://github.com/laurentkneip/opengv.git
RUN cd opengv && mkdir build && cd build && cmake .. && make && make install

#Installing GTest & GMock
WORKDIR /home/Documents
RUN git clone https://github.com/google/googletest.git
RUN cd googletest && mkdir build && cd build && cmake .. && make && make install

#clean
#RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* 
#CMD /bin/bash