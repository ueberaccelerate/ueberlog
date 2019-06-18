#include <nanogui/nanogui.h>
#include <iostream>
using namespace nanogui;
class LoggerViewer : public nanogui::Screen {
public:
    LoggerViewer() : nanogui::Screen(Eigen::Vector2i(1024, 768), "NanoGUI Test") {
        using namespace nanogui;
        Window *window = new Window(this, "Button demo");
        window->setPosition(Vector2i(15, 15));
        window->setLayout(new GroupLayout());
    }
};

int main() {
    try {
        nanogui::init();

        /* scoped variables */ {
            nanogui::ref<LoggerViewer> app = new LoggerViewer();
            app->drawAll();
            app->setVisible(true);
            nanogui::mainloop();
        }

        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        #if defined(_WIN32)
            MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
        #else
            std::cerr << error_msg << std::endl;
        #endif
        return -1;
    }

    return 0;
}
