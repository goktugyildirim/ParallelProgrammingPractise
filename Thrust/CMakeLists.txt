cmake_minimum_required(VERSION 3.5)
project(CUDA_Practise CUDA CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -O3")


# CUDA
add_library(${PROJECT_NAME}_cuda
		include/CudaPractise.h
		src/CudaPractise.cu
		)
set_target_properties(${PROJECT_NAME}_cuda PROPERTIES
		CUDA_SEPARABLE_COMPILATION ON)


# Thrust
set(THRUST_COMPONENTS CPP OMP TBB)
set(THRUST_OPTIONAL_COMPONENTS CUDA)
add_subdirectory(thrust)

include_directories(
		include
		${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
		${EIGEN3_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
        src/main.cpp
		include/CudaPractise.h)

thrust_create_target(
        ThrustTBB
        HOST
        TBB
        DEVICE
        CUDA
        IGNORE_CUB_VERSION_CHECK
)        

find_package (Eigen3 3.3 NO_MODULE)
target_link_libraries(${PROJECT_NAME}
        ThrustTBB
		Eigen3::Eigen
        )

thrust_update_system_found_flags()




