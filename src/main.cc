#include <iostream>
#include <nanogui/nanogui.h>

enum test_enum { Item1 = 0, Item2, Item3 };

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = float(dvar);
std::string str_val = "A string";
test_enum enumval = Item2;
nanogui::Color colval{0.5f, 0.5f, 0.7f, 1.f};

int main() {
  nanogui::init();

  {
    auto *screen = new nanogui::Screen{nanogui::Vector2i{500, 700}, "NanoGUI"};

    bool enabled = true;
    auto *gui = new nanogui::FormHelper{screen};
    nanogui::ref<nanogui::Window> window =
        gui->addWindow(Eigen::Vector2i{10, 10}, "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
    gui->addVariable("string", str_val);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar)->setSpinnable(true);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar)->setSpinnable(true);

    gui->addGroup("Complex types");
    auto *enum_hdl = gui->addVariable("Enumeration", enumval, enabled);
    enum_hdl->setItems({"Item 1", "Item 2", "Item 3"});
    enum_hdl->setCallback([](int val) {
      std::cout << "Item: "
                << "Item " << (val + 1) << '\n';
    });

    gui->addVariable("Color", colval)
        ->setFinalCallback([](const nanogui::Color &c) {
          std::cout << "ColorPicker Final Callback: [" << c.r() << ", " << c.g()
                    << ", " << c.b() << ", " << c.w() << "]\n";
        });
    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed.\n"; });

    screen->setVisible(true);
    screen->performLayout();
    window->center();

    nanogui::mainloop();
  }

  nanogui::shutdown();
  return 0;
}
