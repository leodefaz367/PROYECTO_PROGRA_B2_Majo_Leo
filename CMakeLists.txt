cmake_minimum_required(VERSION 3.16)

project(RegistroJugadores VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# === Archivos del proyecto, usando tus carpetas Cpp / Headers / Ui ===
set(PROJECT_SOURCES
            Cpp/main.cpp
            Cpp/mainwindow.cpp
            Cpp/jugador.cpp
            Cpp/jugadorrepository.cpp


            Headers/mainwindow.h
            Headers/jugador.h
            Headers/jugadorrepository.h


            Ui/mainwindow.ui

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RegistroJugadores
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(RegistroJugadores SHARED
            ${PROJECT_SOURCES}
        )
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RegistroJugadores
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set_target_properties(RegistroJugadores PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Ui"
)

# Decirle a CMake que los headers están en "Headers"
target_include_directories(RegistroJugadores
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)

target_link_libraries(RegistroJugadores PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RegistroJugadores)
endif()

set_target_properties(RegistroJugadores PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RegistroJugadores
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RegistroJugadores)
endif()

