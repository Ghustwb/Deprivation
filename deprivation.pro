QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    detect.cpp \
    main.cpp \
    mainwindow.cpp \
    track/src/BYTETracker.cpp \
    track/src/STrack.cpp \
    track/src/kalmanFilter.cpp \
    track/src/lapjv.cpp \
    track/src/utils.cpp \
    yolox.cpp

HEADERS += \
    config.h \
    detect.h \
    logging.h \
    mainwindow.h \
    yolox.h

FORMS += \
    mainwindow.ui

#Track
INCLUDEPATH += /home/cap/deprivation/track/include

#TensorRT
LIBS += -L/home/cap/TensorRT/lib -lnvinfer
INCLUDEPATH += /home/cap/TensorRT/include
DEPENDPATH += /home/cap/TensorRT/include

#CUDA#
CUDA_SOURCES += decode.cu
CUDA_SDK = "/usr/local/cuda/"   # Path to cuda SDK install
CUDA_DIR = "/usr/local/cuda/"   # Path to cuda toolkit install
# DO NOT EDIT BEYOND THIS UNLESS YOU KNOW WHAT YOU ARE DOING....
SYSTEM_NAME = ubuntu        # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64            # '32' or '64', depending on your system
CUDA_ARCH = sm_60           # Type of CUDA architecture,
                            # for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64/
CUDA_LIBS = -lcuda -lcudart
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
LIBS += $$CUDA_LIBS

# Configuration of the Cuda compiler
#CONFIG(debug, debug|release) {
#    # Debug mode
#    cuda.input  = CUDA_SOURCES
#    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#    cuda.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS \
#                    $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE \
#                    -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda.dependency_type = TYPE_C
#    QMAKE_EXTRA_COMPILERS += cuda
#}
#else {
#    # Release mode
#    cuda.input = CUDA_SOURCES
#    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS \
#                    $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE \
#                    -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda.dependency_type = TYPE_C
#    QMAKE_EXTRA_COMPILERS += cuda
#}



#OpenCV
LIBS += -L/usr/local/lib/ -lopencv_imgcodecs -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio
INCLUDEPATH += /usr/local/include/opencv4
DEPENDPATH += /usr/local/include/opencv4


#Eigen
INCLUDEPATH += /usr/local/include/eigen3



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
