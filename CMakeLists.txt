cmake_minimum_required(VERSION 3.16)

project(Monitoring_MSVC LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if(MSVC)
  # Просить компилятор выдавать сообщения на английском
  add_compile_options("/errorReport:queue" "/nologo")
  add_definitions("/D _CRT_STDIO_ISO_WIDE_SPECIFIERS")
endif()

add_executable(Monitoring_MSVC
  main.cpp
  cpu.h cpu.cpp
  monitoring.h monitoring.cpp

  ram.h ram.cpp

  gpu.h gpu.cpp

  baseMonitoringAction.h
  specialCpuMonitoring.h
  threadGuard.h threadGuard.cpp
  monitoringOverlay.h monitoringOverlay.cpp




)
target_link_libraries(Monitoring_MSVC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Monitoring_MSVC Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS Monitoring_MSVC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
