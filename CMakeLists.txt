cmake_minimum_required(VERSION 3.23)

project(EmbeddedGUIFramework VERSION 1.0.3 LANGUAGES CXX)

add_library(EmbeddedGUIFramework)

# Options
option(EGUI_VISUAL_DEBUG        "Enable visual element debug"       OFF)
option(EGUI_VERBOSE_DEBUG       "Enable verbose element debug"      OFF)

# C++ Standards
set(CMAKE_CXX_STANDARD 17)
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
        src/GUI_Bitmap.cpp
        src/GUI_Bitmap.h
        src/GUI_Image.cpp
        src/GUI_Image.h
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

# Check for display drivers
find_library(ADAFRUIT_GFX_LIB NAMES Adafruit-GFX-Library)
find_library(SDL3_LIB NAMES SDL3 SDL3-static HINTS ${CMAKE_SOURCE_DIR}/libs/)


if(ADAFRUIT_GFX_LIB)
    target_sources(EmbeddedGUIFramework
        PRIVATE
            src/drivers/Adafruit_GFX_driver.cpp
            src/drivers/Adafruit_GFX_driver.h
    )
    target_compile_definitions(EmbeddedGUIFramework PUBLIC ADAFRUIT_DRIVER=1)
    target_link_libraries(EmbeddedGUIFramework PRIVATE Adafruit-GFX-Library::Adafruit-GFX-Library)
elseif(SDL3_LIB)
    find_library(SDL3_IMAGE_LIB NAMES SDL3_image HINTS ${CMAKE_SOURCE_DIR}/libs/)

    if (NOT SDL3_IMAGE_LIB)
        message(WARNING "SDL3 Image library needs to be present")
    endif()

    find_library(SDL3_TTF_LIB NAMES SDL3_ttf HINTS ${CMAKE_SOURCE_DIR}/libs/)

    if (NOT SDL3_TTF_LIB)
        message(WARNING "SDL3 TTF library needs to be present")
    endif()

    target_sources(EmbeddedGUIFramework 
        PRIVATE 
            src/drivers/SDL3/SDL3_driver.cpp
            src/drivers/SDL3/SDL3_driver.h
    )
    target_compile_definitions(EmbeddedGUIFramework PUBLIC SDL3_DRIVER=1)
    target_link_libraries(EmbeddedGUIFramework PRIVATE SDL3::SDL3-shared SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)

else()
    message(WARNING "No display driver found.")
endif()
