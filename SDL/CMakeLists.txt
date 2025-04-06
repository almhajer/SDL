cmake_minimum_required(VERSION 3.20)
project(BK.app VERSION "0.0.1")

# تحديد مستوى C++ المستخدم
set(CMAKE_CXX_STANDARD 17)
set(NAME_APPLICATION_FOLDER "BKgame")
# تحديد مسار ملفات الرأس للمشروع
set(FILE_PROJECT "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PCH_FILE "${FILE_PROJECT}/precompiled.hpp")


set(BUILD_DIR "${CMAKE_BINARY_DIR}/${NAME_APPLICATION_FOLDER}")
set(APP_NAME "BK.app")
set(APP_DIR "${BUILD_DIR}/${APP_NAME}/Contents")
set(APP_BIN_DIR "${APP_DIR}/MacOS")
set(APP_RES_DIR "${APP_DIR}/Resources")
# إنشاء المجلدات داخل .app
file(MAKE_DIRECTORY ${APP_BIN_DIR})
file(MAKE_DIRECTORY ${APP_RES_DIR})
# نسخ الملفات مثل Info.plist و icon.icns إلى المجلدات المناسبة
configure_file("${CMAKE_SOURCE_DIR}/Info.plist" "${APP_DIR}/Info.plist" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/icon.icns" "${APP_RES_DIR}/icon.icns" COPYONLY)


# تضمين ملفات الرأس للمشروع
include_directories(${FILE_PROJECT})

# العثور على مكتبة SDL3 باستخدام pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

# إضافة الملفات المصدرية
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${FILE_PROJECT}/*.hpp"
        "${FILE_PROJECT}/*.h")


# إضافة الملف التنفيذي
add_executable(BK ${SOURCES}
        include/window.hpp
        src/window.cpp)


# تعريف المتغير MY_VARIABLE الذي يحتوي على مسار مجلد الصور
target_compile_definitions(BK PRIVATE FOLDER_IMAGES="${CMAKE_CURRENT_SOURCE_DIR}/images/")

# إعداد ملف التجميع المسبق
target_precompile_headers(BK PRIVATE ${PCH_FILE})

# إضافة مسار ملفات الرأس لمكتبة SDL3
target_include_directories(BK PRIVATE ${SDL3_INCLUDE_DIRS} ${FILE_PROJECT})

# ربط مكتبة SDL3
# Use SDL3_LDFLAGS which usually contains the full linking command
target_link_libraries(BK PRIVATE ${SDL3_LDFLAGS})

# نسخ الملف التنفيذي إلى مجلد MacOS
add_custom_command(TARGET BK POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:BK> ${APP_BIN_DIR}/BK
        COMMENT "نسخ الملف التنفيذي إلى MacOS"
)