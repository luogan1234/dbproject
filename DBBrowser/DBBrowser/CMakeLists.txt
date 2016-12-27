cmake_minimum_required(VERSION 2.8)

project(DBBrowser)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

qt5_wrap_ui(${PROJECT_NAME} mainwindow.ui)

add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
    ../../consts.h ../../query/MyCommands.cpp ../../query/MyCommands.h ../../recmanage/MyTable.cpp
    ../../recmanage/MyTable.h ../../recmanage/MyPage.cpp ../../recmanage/MyPage.h ../../recmanage/MyCol.cpp
    ../../recmanage/MyCol.h ../../recmanage/MyData.cpp ../../recmanage/MyData.h ../../recmanage/TableCols.cpp
    ../../recmanage/TableCols.h ../../searchanalysis/Constraints.cpp ../../searchanalysis/Constraints.h
    ../../searchanalysis/Updates.cpp ../../searchanalysis/Updates.h ../../StaticMethod.h ../../recmanage/MyFileIO.cpp
    ../../recmanage/MyFileIO.h ../../StaticMethod.cpp ../../recmanage/MyValue.cpp ../../recmanage/MyValue.h
    ../../recmanage/MyIndex.cpp ../../recmanage/MyIndex.h ../../recmanage/ModifyInfo.cpp ../../recmanage/ModifyInfo.h
    ../../recmanage/ModifyInfoForCluster.cpp ../../recmanage/ModifyInfoForCluster.h ../../parser/lex.yy.cpp
    ../../parser/parser.tab.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
