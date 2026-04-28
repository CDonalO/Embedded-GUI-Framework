# Embedded-GUI-Framework

Embedded GUI Framework using the arduino framework
This will allow you to create GUIs on displays supported by the adafruit gfx library (future update will remove this dependency)
Currently the gui elements are only interactable via x and y coordinates. i.e. touch screen input. (future update to allow button input)

# Usage

## Components/Elements

See wiki for detailed object documentation (TODO) :)

### GUI_Element

This is a virtual class which is the parent of every object. You cannot directly create this
object.

This element contains the x, y, width, height, colour profiles and more.

### GUI_View

Your code should only contain ONE view.

The view is the main component, the view contains a stack of 'Menus', the menu at the top of the stack is what will be rendered upon calling draw() on the view object.

The view also has a configurable menu bar at the top of the screen which will contain the current menu name along with a back button (if you aren't displaying the top level menu)

You can link buttons to menus for easy navigation.

### GUI_Menu

The menu is just a list of elements.

### GUI_Grid

The grid is a versatile element, it contains a list of elements similar to a menu.
The grid allows you to automatically resize and order elements.

X and Y positioning in the grid is relative to the grids position.

There are three types of grids:

- horizontal
- vertical
- no ordering

These types will determine how each element is placed relative to each other.
If you set the grid attribute to be GRID_ATTRIBUTE_FLEX, then elements will be automatically resized to
fill the maximum width/height of the grid.

You are able to set maximum width/height of each element to prevent an element being resized past this limit.

You can also nest grid elements.

The no ordering grid is essentially the same as the menu, and will use the defined x, y, width, height.

### GUI_Label

This is just a text label.

### GUI_Button

There are two main types of buttons:

- Press Button
- Toggle Button

Each button has different styles that can be used e.g. rounded square button
Buttons can have callback functions attached to them that are called when the button is selected
You can link elements to toggle buttons, e.g. if you want a 'label' to hide when a toggle button is active.

### GUI_Form

This element will allow you to store/retrieve numerical values.
The value that is displayed in the form has to be populated by the configured 'form_value_update_fun' that is required when you create a form object.

You can have multiple unique numerical values associated with a form object.
See examples for more details.

# Debug

Compile time definitions to help debug

```
-DVISUAL_ELEMENT_DEBUG=1
-DVERBOSE_ELEMENT_DEBUG=1
```

# Installation

## Install via platformio

Search for "Embedded GUI Framework"

# Bugs/Suggestions

Any issues you find please create an issue on the github project.
Feel free to suggest improvements/new features or create a pull request if you would like.
