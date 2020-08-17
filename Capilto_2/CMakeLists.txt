####################################
# Project Foo Project              # 
# Plataforms: Win/Linux            #
# Developer: Gelson Rodrigues      #
# geoldery@gmail.com               #
# Boost: 1.67.0                    #
####################################

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

project(foot_couse)
cmake_minimum_required (VERSION 2.8)
 
#------------------- Path's to build ----------------------------#
if(UNIX)#Linux
  # cpp flags
  set(CMAKE_CXX_FLAGS "")
  SET (THIRD_LIBRARYS_PATH "/DEVTRADE/libs/linux")
  #-D_GLIBCXX_USE_CXX11_ABI=0
  set(CMAKE_CXX_FLAGS_RELEASE "-std=c++1z -O2 -isystem ${THIRD_LIBRARYS_PATH}/include -g -lpthread -ldl")
  set(CMAKE_CXX_FLAGS_DEBUG "-std=c++1z -isystem ${THIRD_LIBRARYS_PATH}/include -g -lpthread -ldl")
 
 # set(LIBRARIES_PATH ${PROJECT_PATH}/libraries/linux)
  set(SUFIX_GTEST)
  set(PREFIX_NAME lib)
  
    #Extension libs
  SET(EXTENSION_STATIC_LIB a)
  SET(EXTENSION_DYNAMIC_LIB so)  
    
  SET(Boost_NO_BOOST_CMAKE ON)
  set(Boost_REALPATH      ON)
else(UNIX)#Windows
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  # cpp flags
  set(CMAKE_CXX_FLAGS "/GF /TP /EHsc")
  set(CMAKE_CXX_FLAGS_RELEASE "/W3 /O2 /MD /wd4251 /wd4290 /MP")
  set(CMAKE_CXX_FLAGS_DEBUG "/Z7 /W3 /Od /MDd /GR /wd4251 /wd4290 /MP")

  # linker flags
  set(GLOBAL_LINKER_FLAGS "/INCREMENTAL:NO /LTCG")
  set(GLOBAL_LINKER_FLAGS_DEBUG "/DEBUG")

  set(CMAKE_EXE_LINKER_FLAGS ${GLOBAL_LINKER_FLAGS})
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${GLOBAL_LINKER_FLAGS_DEBUG})

  set(CMAKE_SHARED_LINKER_FLAGS ${GLOBAL_LINKER_FLAGS})
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG ${GLOBAL_LINKER_FLAGS_DEBUG})
  
  set(CMAKE_MODULE_LINKER_FLAGS ${GLOBAL_LINKER_FLAGS})
  set(CMAKE_MODULE_LINKER_FLAGS_DEBUG ${GLOBAL_LINKER_FLAGS_DEBUG})
  
  SET (THIRD_LIBRARYS_PATH "G:/DEVTRADE/libraries/win") 
  set(LIB_SQTLITE_NUM 3)
  
  #On Windows boths are .lib
  SET(EXTENSION_STATIC_LIB lib)
  SET(EXTENSION_DYNAMIC_LIB lib)  

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(SUFIX_GTEST d)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(SUFIX_GTEST)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")  
  
endif(UNIX)
 
set(LIBRARIES_INCLUDE_PATH ${THIRD_LIBRARYS_PATH}/include)
set(LIBRARIES_LIBRARY_PATH ${THIRD_LIBRARYS_PATH}/lib)
set(LIBRARIES_BINARIES_PATH ${THIRD_LIBRARYS_PATH}/bin)
 
 
#------------------- Add extern Libs ----------------------------#
 
#BOOST DEFINITIONS 
 
# Adiciontional variable for boost
set(BOOST_INCLUDEDIR ${LIBRARIES_INCLUDE_PATH})
set(BOOST_LIBRARYDIR ${LIBRARIES_LIBRARY_PATH})  
set(Boost_DIR ${BOOST_LIBRARYDIR})

include_directories("${BOOST_INCLUDEDIR}")
link_directories(${Boost_INCLUDE_DIRS})
set(BOOST_INCLUDEDIR ${LIBRARIES_INCLUDE_PATH}) 
set(BOOST_ROOT  ${LIBRARIES_LIBRARY_PATH})

if(UNIX)
SET(Boost_NO_BOOST_CMAKE ON)
set(Boost_REALPATH      ON)
find_package(Boost 1.67 REQUIRED COMPONENTS thread system filesystem timer chrono date_time locale signals iostreams )

else(UNIX)#Windows
set(Boost_DEBUG TRUE)
set(Boost_USE_MULTITHREADED TRUE)  
set(Boost_USE_MULTITHREAD ON)
set(Boost_TRY_STLPORT ON) 
SET(Boost_USE_STATIC_LIBS   ON) 
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
 
set(Boost_USE_DEBUG_LIBS         ON) # ignore debug libs and 
set(Boost_USE_RELEASE_LIBS       OFF)  # only find release libs
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
 set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and 
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
find_package(Boost 1.67 REQUIRED COMPONENTS thread system filesystem timer chrono date_time locale signals iostreams regex zlib)
 
endif(UNIX)
  
 
if(UNIX)#Linux
#DL DEFINITIONS
set(dl_LIBRARIES "/lib64/libdl.so.2")

#PTHREAD DEFINITIONS
set(pthread_LIBRARIES "/lib64/libpthread.so.0")
endif(UNIX) 

if (WIN32)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS) 
endif (WIN32)

#------------------- Version  ----------------------------#

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(IS_DEBUG TRUE)
    set(Exe_installation ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    set(Libs_installation ${Exe_installation}/lib) 	
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Exe_installation ${CMAKE_CURRENT_BINARY_DIR}/Release)
    set(Libs_installation ${Exe_installation}/lib)
	set(IS_DEBUG FALSE)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
 
#------------------- Add projects  --------------------------#

#-- .exe --#
add_subdirectory(server_proj) 
add_subdirectory(client_proj)  
add_subdirectory(skills_proj) 
