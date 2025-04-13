cmake_minimum_required(VERSION 3.25.0)

project(QtClientTests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17 REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network LinguistTools Test)
include_directories(${Qt6_INCLUDE_DIRS})

enable_testing()

add_executable(
        testClickableLabel
        TestClickableLabel.cpp
)
target_link_libraries(testClickableLabel
        QtClientLibrary
        Qt6::Core
        Qt6::Test
        Qt6::Gui
        Qt6::Widgets
)

add_test(NAME TestClickableLabel COMMAND testClickableLabel)

add_executable(
        testProductCard
        TestProductCard.cpp
)
target_link_libraries(testProductCard
        QtClientLibrary
        Qt6::Core
        Qt6::Test
        Qt6::Gui
        Qt6::Widgets
)

add_test(NAME TestProductCard COMMAND testProductCard)


add_executable(
        testProducts
        TestProducts.cpp
)
target_link_libraries(testProducts
        QtClientLibrary
        Qt6::Core
        Qt6::Test
        Qt6::Gui
        Qt6::Widgets
)

add_test(NAME TestProducts COMMAND testProducts)

add_executable(
        testMainWindow
        TestMainWindow.cpp
        mock/MockRequestMaster.h
        mock/MockPresentator.h
)
target_link_libraries(testMainWindow
        QtClientLibrary
        Qt6::Core
        Qt6::Test
        Qt6::Gui
        Qt6::Widgets
)

add_test(NAME TestMainWindow COMMAND testMainWindow)


add_executable(
        testPresentator
        TestPresentator.cpp
)
target_link_libraries(testPresentator
        QtClientLibrary
        Qt6::Core
        Qt6::Test
        Qt6::Gui
        Qt6::Widgets
)

add_test(NAME TestPresentator COMMAND testPresentator)

#target_include_directories(testGui PUBLIC ${PROJECT_SOURCE_DIR})


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
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Test Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Network )
##
#qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#
#add_executable(test_qt "${SOURCES}")
#
#qt6_add_translations(test_qt TS_FILES test_qt_ru.ts)
#
#target_link_libraries(test_qt Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Network)
