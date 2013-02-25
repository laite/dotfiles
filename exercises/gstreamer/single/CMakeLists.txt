cmake_minimum_required(VERSION 2.6)
project(single)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0 gstreamermm-0.10)

add_subdirectory(src)
