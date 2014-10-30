cmake_minimum_required( VERSION 2.8 )
project( Wind )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

option( WIND_BUILD_SHARED_LIBS "Build shared libraries?"   OFF )
option( WIND_BUILD_EXAMPLES    "Build examples?"           OFF )
option( WIND_INSTALL           "Generate Install target? " ON  )

set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type." )
set( CMAKE_DEBUG_POSTFIX "-d" )

set( WIND_SHARE_DIR share/${CMAKE_PROJECT_NAME} )
if(WIN32)
	set(WIND_SHARE_DIR .)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
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
	${INC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.hpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Engine/Engine.cpp
	${SRC_DIR}/${CMAKE_PROJECT_NAME}/Engine/Entity/Entity.cpp

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
