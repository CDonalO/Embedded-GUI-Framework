cmake_minimum_required(VERSION 3.23)

project(EmbeddedGUIFramework VERSION 1.0.3 LANGUAGES CXX)

add_library(EmbeddedGUIFramework)

# Options
option(EGUI_VISUAL_DEBUG  "Enable visual element debug"   OFF)
option(EGUI_VERBOSE_DEBUG "Enable verbose element debug"  OFF)

set(GUI_IMAGE_SUPPORT FALSE)
set(GUI_DATE_PICKER_SUPPORT FALSE)

# C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

target_sources(EmbeddedGUIFramework
    PRIVATE
        src/GUI_Button.cpp
        src/GUI_Button.h
        src/GUI_Colours.cpp
        src/GUI_Colours.h
        src/GUI_Element.cpp
        src/GUI_Element.h
        src/GUI_Form.cpp
        src/GUI_Form.h
        src/GUI_Label.cpp
        src/GUI_Label.h
        src/GUI_Grid.cpp
        src/GUI_Grid.h
        src/GUI_Menu.cpp
        src/GUI_Menu.h
        src/GUI_View.cpp
        src/GUI_View.h
        src/GUI_Image.cpp
        src/GUI_Image.h
        src/GUI_Slider.cpp
        src/GUI_Slider.h
        src/GUI_Datepicker.cpp
        src/GUI_Datepicker.h
        src/Coordinate.h
        src/Form_Data.cpp
        src/Form_Data.h
        src/Form_Data_Register.h
        src/drivers/display_driver.h
        src/platform.h
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/GUI.h
)

if (EGUI_VISUAL_DEBUG)
    target_compile_definitions(EmbeddedGUIFramework PUBLIC VISUAL_ELEMENT_DEBUG=1)
endif()

if (EGUI_VERBOSE_DEBUG)
    target_compile_definitions(EmbeddedGUIFramework PUBLIC VERBOSE_ELEMENT_DEBUG=1)
endif()

# ── Driver detection ──────────────────────────────────────────────────────────

# Adafruit GFX — find_package is cleaner than find_library for imported targets
find_package(Adafruit-GFX-Library QUIET)

# SDL3 — respect parent project if already added via add_subdirectory/FetchContent
if(NOT TARGET SDL3::SDL3)
    find_package(SDL3 QUIET)
endif()

if(TARGET Adafruit-GFX-Library::Adafruit-GFX-Library)
    message(STATUS "EmbeddedGUI: using Adafruit GFX driver")

    target_sources(EmbeddedGUIFramework PRIVATE
        src/drivers/Adafruit_GFX_driver.cpp
        src/drivers/Adafruit_GFX_driver.h
    )
    target_compile_definitions(EmbeddedGUIFramework PUBLIC ADAFRUIT_DRIVER=1)
    target_link_libraries(EmbeddedGUIFramework
        PRIVATE Adafruit-GFX-Library::Adafruit-GFX-Library
    )

elseif(TARGET SDL3::SDL3)
    message(STATUS "EmbeddedGUI: using SDL3 driver")
    set(GUI_DATE_PICKER_SUPPORT TRUE)

    # SDL3_image
    if(NOT TARGET SDL3_image::SDL3_image)
        find_package(SDL3_image QUIET
            HINTS ${CMAKE_SOURCE_DIR}/libs ${CMAKE_PREFIX_PATH}
        )
    endif()
    if(NOT TARGET SDL3_image::SDL3_image)
        message(WARNING "SDL3_image not found — image support disabled")
    else()
        set(GUI_IMAGE_SUPPORT TRUE)
    endif()

    # SDL3_ttf
    if(NOT TARGET SDL3_ttf::SDL3_ttf)
        find_package(SDL3_ttf QUIET
            HINTS ${CMAKE_SOURCE_DIR}/libs ${CMAKE_PREFIX_PATH}
        )
    endif()
    if(NOT TARGET SDL3_ttf::SDL3_ttf)
        message(WARNING "SDL3_ttf not found — font support may be limited")
    endif()

    target_sources(EmbeddedGUIFramework PRIVATE
        src/drivers/SDL3/SDL3_driver.cpp
        src/drivers/SDL3/SDL3_driver.h
    )
    target_compile_definitions(EmbeddedGUIFramework PUBLIC SDL3_DRIVER=1)

    target_link_libraries(EmbeddedGUIFramework PRIVATE SDL3::SDL3)

    if (TARGET SDL3_ttf::SDL3_ttf)
        target_link_libraries(EmbeddedGUIFramework PRIVATE SDL3_ttf::SDL3_ttf)
    endif()

    if (TARGET SDL3_image::SDL3_image)
        target_link_libraries(EmbeddedGUIFramework PRIVATE SDL3_image::SDL3_image)
    endif()

else()
    message(WARNING "EmbeddedGUI: no display driver found. "
                    "Install SDL3 or Adafruit-GFX-Library, or set CMAKE_PREFIX_PATH.")
endif()


if (GUI_IMAGE_SUPPORT)
    target_compile_definitions(EmbeddedGUIFramework PUBLIC GUI_IMAGE_SUPPORT=1)
endif()

if (GUI_DATE_PICKER_SUPPORT)
    target_compile_definitions(EmbeddedGUIFramework PUBLIC GUI_DATE_PICKER_SUPPORT=1)
endif()