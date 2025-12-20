#include <QApplication>
#include <QWidget>

auto main(int argc, char *argv[]) -> int
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Can Bus Manager");
    window.resize(400, 300);
    window.show();
    return app.exec();
}