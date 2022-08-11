# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("void")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             void

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             main.cpp
             utils.cpp
             hooks.cpp
             menu.cpp
             imgui/imgui.cpp
             imgui/imgui_demo.cpp
             imgui/imgui_draw.cpp
             imgui/imgui_tables.cpp
             imgui/imgui_widgets.cpp
             imgui/imgui_impl_android.cpp
             imgui/imgui_impl_opengl3.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/dobby/include)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/dobby/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       void

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${DOBBY_LIB}
                       android
                       EGL
                       GLESv3)