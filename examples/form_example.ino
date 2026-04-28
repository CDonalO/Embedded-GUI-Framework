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

#define FORM_VALUE_ONE_ID 0
#define FORM_VALUE_TWO_ID 1

bool update_form_value(std::vector<GUI_Form::Form_Number_Data *> *data_stack, char *form_value)
{
  int v1 = GUI_Form::get_form_data_by_id(data_stack, FORM_VALUE_ONE_ID)->get_value();
  int v2 = GUI_Form::get_form_data_by_id(data_stack, FORM_VALUE_TWO_ID)->get_value();

  sprintf((char *)form_value, "%d / %d", v1, v2);
  return false;
}

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

  // Create grid to contain form value modifying buttons
  GUI_Grid *buttons_grid = new GUI_Grid(GRID_TYPE_HORIZONTAL, 0, 4, GRID_ATTRIBUTE_FLEX);

  GUI_Form *test_form = new GUI_Form("Test:", update_form_value);

  // Create form value with min 1 max 10 starting value 1
  test_form->create_number_form_data(FORM_VALUE_ONE_ID, 1, 10, 1);

  // Create form toggle value with default value to false
  test_form->create_toggle_form_data(FORM_VALUE_TWO_ID, false);

  // Fetch buttons to increase form value based on ID
  GUI_Button *increase_one = test_form->get_number_form_button(FORM_VALUE_ONE_ID, true);
  GUI_Button *decrease_one = test_form->get_number_form_button(FORM_VALUE_ONE_ID, false);

  GUI_Toggle_Button *toggle_two = test_form->get_toggle_form_button(FORM_VALUE_TWO_ID);

  main_menu_grid->add_element(test_form);
  main_menu_grid->add_element(buttons_grid);

  buttons_grid->add_element(increase_one);
  buttons_grid->add_element(decrease_one);
  buttons_grid->add_element(toggle_two);

  main_menu->add_element(main_menu_grid);

  view->set_menu(main_menu);
}

void loop()
{
  view->draw();
  delay(1000);
}
