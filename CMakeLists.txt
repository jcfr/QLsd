
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)

#
# Qt Lookup Symbol Definition
#
PROJECT(QLsd)

FIND_PACKAGE(Qt4 4.7 REQUIRED)
INCLUDE(${QT_USE_FILE})

SET(KIT_SRCS
  Main.cpp
  ctkCommandLineParser.cpp
  ctkCommandLineParser.h
  )
  
SET(KIT_MOC_SRCS
  ctkCommandLineParser.h
  )
  
QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
  
ADD_EXECUTABLE(qlsd ${KIT_SRCS} ${KIT_MOC_CPP})
TARGET_LINK_LIBRARIES(qlsd ${QT_LIBRARIES})
