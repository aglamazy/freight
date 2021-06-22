cmake_minimum_required(VERSION 3.19)
project(freight)

set (RESTBED_ROOT "/mnt/data2/restbed_build/restbed")

include_directories("/mnt/data2/restbed_build/restbed/source")

find_library(RESTBED_LIBRARY
        NAMES
        restbed
        PATHS
        ${RESTBED_ROOT}/build
        )

if ( NOT RESTBED_LIBRARY )
    message( WARNING "Restbed library NOT FOUND - the respective targets won't be build")
    message(WARNING ${RESTBED_ROOT})
else()
    message( STATUS "Restbed library : ${RESTBED_LIBRARY}")
endif( NOT RESTBED_LIBRARY )

find_library(mysqlcppconn
        NAMES
        mysqlcppconn)

if ( NOT mysqlcppconn )
    message( WARNING "mysqlcppconn library NOT FOUND - the respective targets won't be build")
    message(WARNING ${RESTBED_ROOT})
else()
    message( STATUS "mysqlcppconn library : ${mysqlcppconn}")
endif( NOT mysqlcppconn )

find_library(curl
        NAMES
        curl
        )

if ( NOT curl )
    message( WARNING "curl library NOT FOUND - the respective targets won't be build")
    message(WARNING ${curl})
else()
    message( STATUS "curl library : ${curl}")
endif( NOT curl )

set(CMAKE_CXX_STANDARD 14)

add_executable(freight main.cpp Freight_Path.cpp Freight_Path.h)

target_link_libraries( "freight" ${RESTBED_LIBRARY} ${mysqlcppconn} ${curl})
