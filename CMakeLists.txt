cmake_minimum_required( VERSION 2.8 )
project( Wind )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

option( WIND_BUILD_SHARED_LIBS "Build shared libraries?"                                OFF )
option( WIND_BUILD_EXAMPLES    "Build examples?"                                        OFF )
option( WIND_INSTALL           "Generate Install target?"                               ON  )
option( WIND_USE_SSE4A         "Use SSE4a CPU optimizations? (Not available for MSVC)"  OFF )
option( WIND_USE_SSE42         "Use SSE4.2 CPU optimizations? (Not available for MSVC)" OFF )
option( WIND_USE_SSE41         "Use SSE4.1 CPU optimizations? (Not available for MSVC)" OFF )
option( WIND_USE_SSE4          "Use SSE4 CPU optimizations? (Not available for MSVC)"   OFF )
option( WIND_USE_SSE3          "Use SSE3 CPU optimizations? (Not available for MSVC)"   OFF )
option( WIND_USE_SSE2          "Use SSE2 CPU optimizations?"                            OFF )
option( WIND_USE_SSE           "Use SSE CPU optimizations?"                             OFF )
option( WIND_USE_NATIVE        "Use GCC native optimizations? (Only on GCC/Similar)"    OFF )

set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type.")
set( CMAKE_DEBUG_POSTFIX "-d" )

set( WIND_SHARE_DIR share/${CMAKE_PROJECT_NAME} )
if(WIN32)
	set(WIND_SHARE_DIR .)
endif()


if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

	if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	endif()

	if(WIND_USE_NATIVE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
	endif()

	if(WIND_USE_SSE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -mfpmath=sse")
	endif()
	if(WIND_USE_SSE2)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -mfpmath=sse")
	endif()
	if(WIND_USE_SSE3)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3 -mfpmath=sse")
	endif()
	if(WIND_USE_SSE4)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4 -mfpmath=sse")
	endif()
	if(WIND_USE_SSE41)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -mfpmath=sse")
	endif()
	if(WIND_USE_SSE42)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -mfpmath=sse")
	endif()
	if(WIND_USE_SSE4A)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4a -mfpmath=sse")
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
	endif()
	if(WIND_USE_SSE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
	endif()
	if(WIND_USE_SSE2)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	if(WIND_USE_SSE3)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	if(WIND_USE_SSE4)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	if(WIND_USE_SSE41)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	if(WIND_USE_SSE42)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	if(WIND_USE_SSE4A)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
endif()

if(WIND_BUILD_SHARED_LIBS)
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

set(SRC_DIR "src")
set(INC_DIR "include")
set(EXA_DIR "examples")

set(
	SOURCES
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Engine/Engine.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Engine/Engine.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Integration/Euler.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Integration/Euler.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Integration/RK4.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Integration/RK4.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Body/Body.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Body/Body.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/AABB/AABB.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/AABB/AABB.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Partitioning/Partitioning.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Partitioning/QuadTree.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Partitioning/QuadTree.cpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Partitioning/Grid.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Partitioning/Grid.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/Shape.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/Shape.cpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/CircleShape.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/CircleShape.cpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/RectangleShape.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Shape/RectangleShape.cpp

	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2/Vector2.hpp
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Maths/Vector2/Vector2.inl
)

include_directories( ${INC_DIR} )
include_directories( ${SRC_DIR} )

add_library( ${CMAKE_PROJECT_NAME} ${LIB_TYPE} ${SOURCES} )

if(WIND_BUILD_EXAMPLES)
	add_subdirectory(${EXA_DIR})
endif()

if(WIND_INSTALL)
	install(DIRECTORY ${INC_DIR} DESTINATION .)
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)

	install(FILES README.md LICENSE
		DESTINATION ${WIND_SHARE_DIR}
	)
endif()
