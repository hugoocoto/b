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
#include <QWebEngineProfile>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineView>

#include "config.h"

void
open_url(QWebEngineView *view, const QString input)
{
        QUrl url = QUrl::fromUserInput(input);

        if (url.isLocalFile()) {
                qDebug() << "NO YET IMPLEMENTED: local file:" << url.toString();

        } else if (url.isValid() && url.host().contains(".")) {
                view->setUrl(url);

        } else {
                url = QUrl(search_engine);
                QUrlQuery query;
                query.addQueryItem("q", input);
                url.setQuery(query);
                view->setUrl(url);
        }
}

int
main(int argc, char *argv[])
{
        QWidget *floating;
        QHBoxLayout *floating_layout;
        QLineEdit *line_edit;
        QLabel *url_element;
        QWebEngineView *view;
        QWidget *window;
        QVBoxLayout *layout;
        QWebEngineProfile *profile;
        QWebEnginePage *page;

#if defined(GLANGLE)
        // just because It doesn't find my vulkan and it's slow as f*ck
        QByteArray flags = "--use-gl=angle --use-angle=gl --enable-gpu-rasterization --enable-zero-copy --ignore-gpu-blocklist";
        qputenv("QTWEBENGINE_CHROMIUM_FLAGS", flags);
#endif

        QApplication app(argc, argv);

        // cookies
        profile = new QWebEngineProfile(QString::fromLatin1("b.%1").arg(qWebEngineChromiumVersion()));
        page = new QWebEnginePage(profile);

        // Content
        view = new QWebEngineView();
        view->setPage(page);
        if (startup_page) view->setUrl(QUrl(startup_page));

        // Change url_element text on urlChanged
        QObject::connect(view->page(), &QWebEnginePage::urlChanged,
                         [&](const QUrl &url) {
                                 url_element->setMaximumWidth(window->width()); // todo: change this
                                 url_element->setText(url.toString());
                         });

        // URL bar
        url_element = new QLabel(default_url_text ?: "");
        url_element->setFixedHeight(30);

        // Main window
        window = new QWidget;
        window->show();

        // Main window layout
        layout = new QVBoxLayout(window);
        layout->addWidget(url_element);
        layout->addWidget(view);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);

        // Url user modification widget
        floating = new QWidget(window);
        floating->setFixedSize(URL_INPUT_SIZE);
        floating_layout = new QHBoxLayout(floating);
        floating_layout->setContentsMargins(URL_INPUT_MARGIN);
        floating_layout->setSpacing(URL_INPUT_SPACING);
        line_edit = new QLineEdit(floating);
        floating_layout->addWidget(line_edit);
        QObject::connect(line_edit, &QLineEdit::returnPressed, [=]() {
                open_url(view, line_edit->text());
                floating->hide();
                line_edit->clear();
        });

        // Ctrl+L for opening search bar
        QShortcut *shortcut = new QShortcut(QKeySequence(url_input_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [&]() {
                if (floating->isVisible())
                        floating->hide();
                else {
                        int x = (window->width() - floating->width()) / 2;
                        int y = (window->height() - floating->height()) / 2;
                        floating->move(x, y);
                        floating->show();
                        line_edit->setFocus();
                        line_edit->setText(url_element->text());
                        line_edit->selectAll();
                }
        });

        return app.exec();
}
