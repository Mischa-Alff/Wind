set(EXAMPLE_NAME testbench)
set(EXAMPLE_SRC
	${CMAKE_SOURCE_DIR}/examples/${EXAMPLE_NAME}/${EXAMPLE_NAME}.cpp
)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR})

add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})

target_link_libraries(${EXAMPLE_NAME} ${SFML_LIBRARIES})
target_link_libraries(${EXAMPLE_NAME} ${CMAKE_PROJECT_NAME})

if(WIND_INSTALL)
	set(EXAMPLE_INSTALL_DIR ${WIND_SHARE_DIR}/${EXA_DIR}/${EXAMPLE_NAME})
	install(
		TARGETS ${EXAMPLE_NAME}
		RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR} COMPONENT bin
	)
	install(
		FILES ${EXAMPLE_SRC}
		DESTINATION ${EXAMPLE_INSTALL_DIR}
	)
endif()
