cmake_minimum_required ( VERSION 3.5 )

project ( LoLCDB LANGUAGES CXX )

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin )

find_package ( CURL REQUIRED )

include_directories ( include ${CURL_INCLUDE_DIR} )

add_subdirectory ( src )
