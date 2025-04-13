cmake_minimum_required(VERSION 3.25.0)

project(QtClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network LinguistTools Test)
include_directories(${Qt6_INCLUDE_DIRS})

qt_add_executable(${PROJECT_NAME} main.cpp resource.qrc)

#
#add_library(QtClientLibrary
#        src/requestMaster.cpp
#        main.cpp
#        src/main_window.cpp
#        src/presentator.cpp
#        src/widgets/CircleImage.cpp
#        src/widgets/ClicableLabel.cpp
#        src/widgets/ProductCard.cpp
#        src/widgets/Products.cpp
#        resource.qrc
#)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

#set(TS_FILES translations/helloworld_ru.ts)
#qt6_create_translation(QM_FILES ${SOURCES} ${TS_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE QtClientLibrary Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Network )

#
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        WIN32_EXECUTABLE TRUE
#)
#
#include(GNUInstallDirs)
#install(TARGETS ${PROJECT_NAME}
#        BUNDLE DESTINATION .
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(${PROJECT_NAME})
#endif() Qt6::Gui


#
#qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#
#add_executable(test_qt "${SOURCES}")
#
#qt6_add_translations(test_qt TS_FILES test_qt_ru.ts)
#
#target_link_libraries(test_qt Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Network)
