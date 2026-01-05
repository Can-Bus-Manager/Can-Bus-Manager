#include <QApplication>

#include "app_root.hpp"

/**
 * @brief Application Entry Point.
 * @details Initializes the Qt environment and hands control to the AppRoot kernel.
 */
auto main(int argc, char* argv[]) -> int
{
    QApplication app(argc, argv);
    // AppRoot::AppRoot kernel;
    // kernel.bootstrap();
    QWidget window;
    window.setWindowTitle("Can Bus Manager");
    window.resize(400, 300);
    window.show();
    return app.exec();
}