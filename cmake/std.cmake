# compile the std lib as a module (for LLVM & MSVC only)

# extract the compiler directory
get_filename_component(COMPILER_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
if(MSVC)
    set(STD_BASE_DIR ${COMPILER_DIR}/../../../modules)
    set(STD_EXTENSION ixx)
else()
    set(STD_EXTENSION cppm)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "This project require Clang and libc++")
    endif()

    string(REGEX MATCH "^[0-9]+" LLVM_MAJOR "${CMAKE_CXX_COMPILER_VERSION}")
    get_filename_component(COMPILER_PREFIX "${COMPILER_DIR}/.." ABSOLUTE)
    set(_llvm_prefixes
        "${COMPILER_PREFIX}"
        "${COMPILER_PREFIX}/lib/llvm-${LLVM_MAJOR}"
        "/usr/lib/llvm-${LLVM_MAJOR}"
        "/usr/local/llvm-${LLVM_MAJOR}"
        "/usr/local"
        "/usr"
        "/opt/homebrew/opt/llvm"
        "/usr/local/opt/llvm"
    )

    if(NOT DEFINED STD_BASE_DIR)
        foreach(_prefix IN LISTS _llvm_prefixes)
            foreach(_module_rel IN ITEMS "share/libc++/v1" "share/libc++")
                if(EXISTS "${_prefix}/${_module_rel}/std.cppm")
                    set(_candidate_include "")
                    foreach(_include_rel IN ITEMS "include/c++/v1" "include/${LLVM_MAJOR}/c++/v1")
                        if(EXISTS "${_prefix}/${_include_rel}/__config")
                            set(_candidate_include "${_prefix}/${_include_rel}")
                            break()
                        endif()
                    endforeach()
                    if(_candidate_include)
                        set(STD_BASE_DIR "${_prefix}/${_module_rel}")
                        if(NOT DEFINED STD_INCLUDE_DIR)
                            set(STD_INCLUDE_DIR "${_candidate_include}")
                        endif()
                        break()
                    endif()
                endif()
            endforeach()
            if(DEFINED STD_BASE_DIR)
                break()
            endif()
        endforeach()
    endif()

    if(NOT DEFINED STD_BASE_DIR OR NOT EXISTS "${STD_BASE_DIR}/std.cppm")
        message(FATAL_ERROR
            "libc++ std.cppm not found for Clang ${LLVM_MAJOR}. "
            "Install the corresponding libc++-dev package or specify -DSTD_BASE_DIR=/path/to/libc++/v1 if installed elsewhere.")
    endif()
    if(NOT DEFINED STD_INCLUDE_DIR)
        get_filename_component(_module_prefix "${STD_BASE_DIR}/../../.." ABSOLUTE)
        foreach(_include_rel IN ITEMS "include/c++/v1" "include/${LLVM_MAJOR}/c++/v1")
            if(EXISTS "${_module_prefix}/${_include_rel}/__config")
                set(STD_INCLUDE_DIR "${_module_prefix}/${_include_rel}")
                break()
            endif()
        endforeach()
    endif()
    if(NOT DEFINED STD_INCLUDE_DIR OR NOT EXISTS "${STD_INCLUDE_DIR}/__config")
        message(FATAL_ERROR
            "Matching libc++ headers not found. Install the corresponding package or specify -DSTD_INCLUDE_DIR=/path/to/include/c++/v1.")
    endif()
endif()

if(NOT EXISTS ${STD_BASE_DIR}/std.${STD_EXTENSION})
    message(FATAL_ERROR "std.${STD_EXTENSION}")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-stdlib=libc++)
	add_link_options(-stdlib=libc++)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_link_options(-static-libstdc++)
    endif()
endif()

add_library(std-cxx-modules STATIC)
target_sources(std-cxx-modules
        PUBLIC
        FILE_SET moduleStd
        TYPE CXX_MODULES
        BASE_DIRS ${STD_BASE_DIR}
        FILES
        ${STD_BASE_DIR}/std.${STD_EXTENSION}
        ${STD_BASE_DIR}/std.compat.${STD_EXTENSION})
set_target_properties(std-cxx-modules PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(std-cxx-modules PRIVATE
            /std:c++latest
            /experimental:module
            /EHsc
            /nologo
            /W4
            /c
            /fp:fast
    )
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(std-cxx-modules PRIVATE
                /Od
                /D_DEBUG
                /MDd
        )
    else()
        target_compile_options(std-cxx-modules PRIVATE
                /O2
                /MD
        )
    endif()
else()
    target_compile_options(std-cxx-modules
            PUBLIC
            -Wno-reserved-module-identifier
            -Wno-reserved-user-defined-literal
    )
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(std-cxx-modules PRIVATE
                -O0
        )
    else()
        target_compile_options(std-cxx-modules PRIVATE
                -O3
        )
    endif()
endif()
