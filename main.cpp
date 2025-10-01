#include "qlogging.h"
#include "qwidget.h"
#include <QApplication>
#include <QByteArray>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QShortcut>
#include <QUrl>
#include <QUrlQuery>
#include <QVBoxLayout>
#include <QWebEnginePage>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineView>

void
open_url(QWebEngineView *view, const QString input)
{
        QUrl url = QUrl::fromUserInput(input);

        if (url.isLocalFile()) {
                qDebug() << "NO YET IMPLEMENTED: local file:" << url.toString();

        } else if (url.isValid() && url.host().contains(".")) {
                view->setUrl(url);

        } else {
                url = QUrl("https://www.google.com/search");
                QUrlQuery query;
                query.addQueryItem("q", input);
                url.setQuery(query);
                view->setUrl(url);
        }
}

int
main(int argc, char *argv[])
{
        QLabel *url_element;
        QWebEngineView *view;
        QWidget *window;
        QVBoxLayout *layout;

        // just because It doesn't find my vulkan and it's slow as f*ck
        QByteArray flags = "--use-gl=angle --use-angle=gl --enable-gpu-rasterization --enable-zero-copy --ignore-gpu-blocklist";
        qputenv("QTWEBENGINE_CHROMIUM_FLAGS", flags);

        QApplication app(argc, argv);

        // Content
        view = new QWebEngineView();
        view->setUrl(QUrl("https://www.hugocoto.com/"));

        // Change url_element text on urlChanged
        QObject::connect(view->page(), &QWebEnginePage::urlChanged,
                         [&](const QUrl &url) {
                                 url_element->setText(url.toString());
                         });

        // URL bar
        url_element = new QLabel("This is the url bar");
        url_element->setFixedHeight(30);

        // Main window
        window = new QWidget;
        window->show();

        // Main window layour
        layout = new QVBoxLayout(window);
        layout->addWidget(url_element);
        layout->addWidget(view);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // Url user modification widget
        QWidget *floating = new QWidget(window);
        floating->setFixedSize(300, 30);
        QHBoxLayout *floating_layout = new QHBoxLayout(floating);
        floating_layout->setContentsMargins(0, 0, 0, 0);
        floating_layout->setSpacing(0);
        QLineEdit *line_edit = new QLineEdit("", floating);
        floating_layout->addWidget(line_edit);
        QObject::connect(line_edit, &QLineEdit::returnPressed, [=]() {
                open_url(view, line_edit->text());
                floating->hide();
                line_edit->clear();
        });

        // Atajo Ctrl+L para mostrar/ocultar
        QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+L"), window);
        QObject::connect(shortcut, &QShortcut::activated, [&]() {
                if (floating->isVisible())
                        floating->hide();
                else {
                        int x = (window->width() - floating->width()) / 2;
                        int y = (window->height() - floating->height()) / 2;
                        floating->move(x, y);
                        floating->show();
                        // floating->raise();
                        line_edit->setFocus();
                        line_edit->setText(url_element->text());
                        line_edit->selectAll();
                }
        });

        return app.exec();
}
