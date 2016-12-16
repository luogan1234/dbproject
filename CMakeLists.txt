cmake_minimum_required(VERSION 2.8)
project(dbproject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp consts.h query/MyCommands.cpp query/MyCommands.h recmanage/MyTable.cpp recmanage/MyTable.h recmanage/MyPage.cpp recmanage/MyPage.h recmanage/MyCol.cpp recmanage/MyCol.h recmanage/MyData.cpp recmanage/MyData.h recmanage/TableCols.cpp recmanage/TableCols.h searchanalysis/Constraints.cpp searchanalysis/Constraints.h searchanalysis/Updates.cpp searchanalysis/Updates.h StaticMethod.h recmanage/MyFileIO.cpp recmanage/MyFileIO.h StaticMethod.cpp recmanage/MyValue.cpp recmanage/MyValue.h recmanage/MyIndex.cpp recmanage/MyIndex.h recmanage/ModifyInfo.cpp recmanage/ModifyInfo.h recmanage/ModifyInfoForCluster.cpp recmanage/ModifyInfoForCluster.h parser/lex.yy.cpp parser/parser.tab.cpp)
add_executable(dbproject ${SOURCE_FILES})
