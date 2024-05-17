cmake_minimum_required(VERSION 3.16)

project(COM-port_graphs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core SerialPort Charts)

qt_standard_project_setup()

qt_add_executable(appCOM-port_graphs
    main.cpp
)

qt_add_qml_module(appCOM-port_graphs
    URI COM-port_graphs
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        serialportreader.cpp
        serialportreader.h
        comemulator.cpp
        comemulator.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCOM-port_graphs PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCOM-port_graphs
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCOM-port_graphs
    PRIVATE Qt6::Quick Qt6::Core Qt6::SerialPort Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appCOM-port_graphs
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
