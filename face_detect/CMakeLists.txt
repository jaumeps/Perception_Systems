#indicate minimum version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#project name
PROJECT(face_detection)

#find required packages (look for the package, usually at /usr/share/cmake-2.8/Modules/ or /usr/share/)
FIND_PACKAGE(OpenCV REQUIRED)

#set header directories
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})

#Create an executable
ADD_EXECUTABLE(face_detection_haar_video src/face_detection_haar_video.cpp)
ADD_EXECUTABLE(face_detection_haar_webcam src/face_detection_haar_webcam.cpp)
ADD_EXECUTABLE(face_detection_haar_video_hat_moustache src/face_detection_haar_video_hat_moustache.cpp)
ADD_EXECUTABLE(face_detection_haar_webcam_hat_moustache src/face_detection_haar_webcam_hat_moustache)
ADD_EXECUTABLE(face_detection_LBP_video src/face_detection_LBP_video.cpp)
ADD_EXECUTABLE(face_detection_LBP_webcam src/face_detection_LBP_webcam.cpp)
ADD_EXECUTABLE(test_video src/face_detection_plus_video.cpp)
ADD_EXECUTABLE(test_webcam src/face_detection_plus_webcam.cpp)

#Link with libraries
TARGET_LINK_LIBRARIES(face_detection_haar_video ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(face_detection_haar_webcam ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(face_detection_haar_video_hat_moustache ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(face_detection_haar_webcam_hat_moustache ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(face_detection_LBP_video ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(face_detection_LBP_webcam ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(test_video ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(test_webcam ${OpenCV_LIBS})
