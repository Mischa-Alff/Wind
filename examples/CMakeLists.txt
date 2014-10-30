set( WIND_INCLUDE_DIR "${CMAKE_PROJECT_DIR}/include/" )
set( WIND_LIBRARY_DIR "${CMAKE_PROJECT_DIR}/")

mark_as_advanced( WIND_INCLUDE_DIR )
mark_as_advanced( WIND_LIBRARY_DIR )

add_subdirectory(testbench)
