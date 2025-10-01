#include <QApplication>
#include <QWebEngineView>

int
main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        QWebEngineView view;
        view.setUrl(QUrl("https://google.com/"));
        view.resize(1024, 768);
        view.show();

        return app.exec();
}
