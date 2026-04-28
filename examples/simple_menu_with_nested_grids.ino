#include <Adafruit_ILI9341.h>
#include <GUI.h>

/* ILI9341 Definitions */
#define ILI_RST 9
#define ILI_CS 10
#define ILI_DC 8
#define ILI_SCK 12
#define ILI_MOSI 11
#define ILI_MISO 13

SPIClass spi_ili(HSPI);
Adafruit_ILI9341 ILI9341 = Adafruit_ILI9341(&spi_ili, ILI_DC, ILI_CS, ILI_RST);
GUI_View *view;

void setup()
{
  Serial.begin(115200);

  spi_ili.begin(ILI_SCK, ILI_MISO, ILI_MOSI, ILI_CS);

  ILI9341.begin();
  ILI9341.setRotation(3);
  ILI9341.setTextSize(2);

  // Set menu bar size to 30
  view = new GUI_View(&ILI9341, 30);
  view->set_width(ILI9341.width());
  view->set_height(ILI9341.height());

  // Create main menu
  GUI_Menu *main_menu = new GUI_Menu("Main Menu");

  main_menu->set_background_colour(ILI9341_BLUE);

  // Create grid with 5 px border padding and 4 px element padding
  GUI_Grid *main_menu_grid = new GUI_Grid(GRID_TYPE_VERTICAL, 5, 4, GRID_ATTRIBUTE_FLEX);

  // Create nested grid
  GUI_Grid *main_menu_nested_grid = new GUI_Grid(GRID_TYPE_HORIZONTAL, 0, 4, GRID_ATTRIBUTE_FLEX);

  GUI_Button *b1 = new GUI_Button(BUTTON_ROUND_STYLE, "Button 1");
  GUI_Button *b2 = new GUI_Button(BUTTON_SQUARE_STYLE, "Button 2");

  GUI_Button *b3 = new GUI_Button(BUTTON_ROUND_STYLE, "Button 3");
  GUI_Button *b4 = new GUI_Button(BUTTON_SQUARE_STYLE, "Button 4");

  main_menu_grid->add_element(b1);
  main_menu_grid->add_element(b2);
  main_menu_grid->add_element(main_menu_nested_grid);

  main_menu_nested_grid->add_element(b3);
  main_menu_nested_grid->add_element(b4);

  main_menu->add_element(main_menu_grid);

  view->set_menu(main_menu);
}

void loop()
{
  view->draw();
  delay(1000);
}
