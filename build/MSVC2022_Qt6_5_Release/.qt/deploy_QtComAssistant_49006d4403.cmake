include(P:/Qt/QtComAssistant/build/MSVC2022_Qt6_5_Release/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/QtComAssistant-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets;SerialPort;Core5Compat")

qt6_deploy_runtime_dependencies(
    EXECUTABLE P:/Qt/QtComAssistant/build/MSVC2022_Qt6_5_Release/QtComAssistant.exe
    GENERATE_QT_CONF
)
