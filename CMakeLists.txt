cmake_minimum_required(VERSION 3.3)
project(bud)

# 声明一些编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

# 单独把主函数文件放出来
set(MAIN_FILE ${PROJECT_SOURCE_DIR}/main.cpp)

# 搜索工程目录，这里是所有bud的源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/bud BUD_SOURCE_FILES)

# 合并要编译可执行文件所需要的源文件和编译库所需要的源文件
list(APPEND EXE_SOURCE_FILES ${MAIN_FILE} ${BUD_SOURCE_FILES})
list(APPEND LIB_SOURCE_FILES ${BUD_SOURCE_FILES})

# 编译可执行文件，其作用是用来测试bud引擎
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(bud ${EXE_SOURCE_FILES})
target_link_libraries(bud SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# 编译静态库文件，注意在使用的时候调用次序，就像如下链接：
# target_link_libraries(Target bud SDL2 SDL2_image SDL2_ttf SDL2_mixer)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(libbud STATIC ${LIB_SOURCE_FILES})
set_target_properties(libbud PROPERTIES OUTPUT_NAME bud)

# 设置输出目录在源文件夹目录下，方便在开发过程中被其他工程调用
set(LOCAL_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/build)
set_target_properties(bud PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LOCAL_OUTPUT_DIR}/bin)
set_target_properties(libbud PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LOCAL_OUTPUT_DIR}/lib)
