cmake_minimum_required(VERSION 2.8)
project(dbproject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp consts.h recmanage/MyTable.cpp recmanage/MyTable.h recmanage/MyPage.cpp recmanage/MyPage.h recmanage/MyCol.cpp recmanage/MyCol.h recmanage/MyData.cpp recmanage/MyData.h recmanage/TableCols.cpp recmanage/TableCols.h searchanalysis/Constraints.cpp searchanalysis/Constraints.h searchanalysis/Updates.cpp searchanalysis/Updates.h StaticMethod.h recmanage/MyFileIO.cpp recmanage/MyFileIO.h StaticMethod.cpp)
add_executable(dbproject ${SOURCE_FILES})
