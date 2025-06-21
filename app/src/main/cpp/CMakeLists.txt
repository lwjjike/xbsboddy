# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.5)

# Declares the project name.
project("ndktest1")

set(CMAKE_CXX_STANDARD 17)

# 添加Dobby子目录（现在CMakeLists.txt在cpp目录下，所以是相对路径）
add_subdirectory(Dobby)

# Creates and names a library
add_library(${CMAKE_PROJECT_NAME} SHARED
        # 现在native-lib.cpp在同一目录下
        native-lib.cpp)

# Specifies libraries CMake should link to your target library
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        dobby  # Dobby库引用
        android
        log)

# 包含Dobby头文件目录
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        Dobby/include)