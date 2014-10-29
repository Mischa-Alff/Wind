cmake_minimum_required( VERSION 2.8 )
project( Windtunnel )

set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE )

if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})

set(SRC_DIR "src")
set(INC_DIR "include")

set(
	SOURCES
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Engine/Engine.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Engine/Engine.cpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2/Vector2.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2/Vector2.inl

	${SRC_DIR}/${CMAKE_PROJECT_NAME}/main.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SRC_DIR} )

add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${CMAKE_PROJECT_NAME} ${SFML_LIBRARIES} )
