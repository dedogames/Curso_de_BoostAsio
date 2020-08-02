project (client)

file(GLOB_RECURSE client_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE client_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp")
set (client_INCLUDE_DIRS "")
foreach (_headerFile ${client_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND client_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES client_INCLUDE_DIRS)
IF (WIN32)
file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH) 
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
	#message("${_group_path}"  "--${_source_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
endif()
#set(libs_SOURCES /projects/crystal_3/trunk/components)
add_executable(client ${client_SOURCES} ${client_HEADERS})
target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source/")

set(client_BUILD_DIRECTORY "${Exe_installation}/client_proj/client")

if(WIN32)
	set(LIBS_WIN ${Boost_REGEX_LIBRARIES}
                     ${Boost_ZLIB_LIBRARIES})	
	if(IS_DEBUG)
		set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${client_BUILD_DIRECTORY})

	else(IS_DEBUG)
		 set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${client_BUILD_DIRECTORY})
	endif(IS_DEBUG)
else(WIN32)
               set(LIBS_WIN )
	set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${client_BUILD_DIRECTORY})
endif(WIN32)

install(TARGETS client DESTINATION bin) 
set(CLIENT_TARGET_LIBRARIES 
      ${Boost_FILESYSTEM_LIBRARY}
      ${Boost_THREAD_LIBRARY}
      ${Boost_SYSTEM_LIBRARY}
      ${Boost_THREAD_LIBRARIES}
      ${Boost_DATE_TIME_LIBRARIES}
      ${Boost_FILESYSTEM_LIBRARIES}
      ${Boost_SYSTEM_LIBRARIES}
      ${Boost_TIMER_LIBRARIES}
      ${Boost_CHRONO_LIBRARIES}
      ${LIBS_WIN}        
   )
list(REMOVE_DUPLICATES CLIENT_TARGET_LIBRARIES) 
target_link_libraries(client ${CLIENT_TARGET_LIBRARIES})
