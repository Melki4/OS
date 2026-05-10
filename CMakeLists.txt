cmake_minimum_required(VERSION 3.19)
project(server_part LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Sql)

qt_standard_project_setup()

qt_add_executable(server_part
    WIN32 MACOSX_BUNDLE
    main.cpp
    dialog.cpp
    dialog.h
    dialog.ui
    databasemanager.h databasemanager.cpp
    logger.h logger.cpp
    barberworker.h barberworker.cpp
    serverdialog.h serverdialog.cpp
    listenerworker.h listenerworker.cpp

)

target_link_libraries(server_part
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Sql
)

install(TARGETS server_part
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET server_part
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
