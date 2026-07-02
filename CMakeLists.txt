cmake_minimum_required(VERSION 3.19)
project(QtComAssistant LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialPort Core5Compat LinguistTools)

qt_standard_project_setup()

qt_add_executable(
    QtComAssistant
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h mainwindow.cpp
    utils.h utils.cpp
    serialservice.h serialservice.cpp
    commanddialog.h commanddialog.cpp
    QtComAssistant_zh_CN.ts
)

qt_add_translations(
    QtComAssistant
    TS_FILES QtComAssistant_zh_CN.ts
)

target_link_libraries(QtComAssistant
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::SerialPort
        Qt::Core5Compat
)

install(TARGETS QtComAssistant
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QtComAssistant
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
