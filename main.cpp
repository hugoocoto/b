#include <QApplication>
#include <QByteArray>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QObject>
#include <QPushButton>
#include <QShortcut>
#include <QUrl>
#include <QUrlQuery>
#include <QVBoxLayout>
#include <QWebEngineHistory>
#include <QWebEngineHistoryItem>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineView>
#include <cstring>

#include "config.h"
#include "qcoreapplication.h"
#include "qlistwidget.h"
#include "qwebenginehistory.h"
#include "qwebengineview.h"

void
open_url(QWebEngineView *view, const QString input)
{
        QUrlQuery query;
        QUrl url;

        url = QUrl::fromUserInput(input);

        if (url.isLocalFile()) {
                qDebug() << "NO YET IMPLEMENTED: local file:" << url.toString();

        } else if (url.isValid() && url.host().contains(".")) {
                view->setUrl(url);

        } else {
                url = QUrl(search_engine);
                query.addQueryItem("q", input);
                url.setQuery(query);
                view->setUrl(url);
        }
}

void
get_history_matches(QWebEngineView *view, QListWidget *list, QString match)
{
        QWebEngineHistory *hist = view->history();
        hist->items();

        list->clear();
        for (QWebEngineHistoryItem item : hist->items()) {
                if (match.isEmpty() || item.url().toString().contains(match))
                        list->addItem(item.url().toString());
        }
}

int
main(int argc, char *argv[])
{
        QWidget *floating;
        QWidget *history_widget;
        QHBoxLayout *floating_layout;
        QVBoxLayout *history_layout;
        QLineEdit *line_edit;
        QLineEdit *hist_edit;
        QLabel *url_element;
        QWebEngineView *view;
        QWidget *window;
        QVBoxLayout *layout;
        QWebEngineProfile *profile;
        QWebEnginePage *page;
        QFont font;

        // Show help message before load anything
        if (argc == 2 && !strcmp(argv[1], "--help")) {
                printf("The b browser! By Hugo Coto\n");
                printf("Usage: %s [--help, url] -> "
                       "Launch b and open url if provided\n",
                       argv[0]);
                return 0;
        }

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

        // font
        font = QFont(font_family);
        font.setPixelSize(font_pxsize);

        // URL bar
        url_element = new QLabel(default_url_text ?: "");
        url_element->setFixedHeight(URLBAR_HEIGHT);
        url_element->setFont(font);
        url_element->setStyleSheet(URLBAR_STYLE);

        // Main window
        window = new QWidget;
        window->show();

        // Main window layout
        layout = new QVBoxLayout(window);
        layout->addWidget(url_element);
        layout->addWidget(view);
        layout->setContentsMargins(URL_BAR_MARGIN);
        layout->setSpacing(URL_BAR_SPACING);

        // Url user modification widget
        floating = new QWidget(window);
        floating->setFixedSize(URL_INPUT_SIZE);
        floating_layout = new QHBoxLayout(floating);
        floating_layout->setContentsMargins(URL_INPUT_MARGIN);
        floating_layout->setSpacing(URL_INPUT_SPACING);
        line_edit = new QLineEdit(floating);
        line_edit->setFont(font);
        line_edit->setTextMargins(TEXT_MARGIN);
        line_edit->setStyleSheet(INPUT_STYLE);
        line_edit->setFixedHeight((URL_INPUT_SIZE));
        floating_layout->addWidget(line_edit);

        QObject::connect(line_edit, &QLineEdit::returnPressed, [=]() {
                open_url(view, line_edit->text());
                floating->hide();
                line_edit->clear();
        });

        // history widget
        history_widget = new QWidget(window);
        history_widget->setFixedSize(600, 300);
        history_widget->setFont(font);
        history_widget->setStyleSheet("background-color: " BG_COLOR ";"
                                      "border-radius: 10px;"
                                      "color: " FG_COLOR ";"
                                      "border: 3px solid " FG_COLOR ";");
        history_layout = new QVBoxLayout(history_widget);
        history_layout->setContentsMargins(0, 0, 0, 0);
        history_layout->setSpacing(0);
        hist_edit = new QLineEdit(history_widget);
        hist_edit->setFont(font);
        hist_edit->setTextMargins(TEXT_MARGIN);
        hist_edit->setStyleSheet("color: " FG_COLOR ";"
                                 "border-radius: 0 0 10px 10px;"
                                 "background-color: " BG_COLOR ";"
                                 "border-bottom: 1px solid " BLACK ";");
        hist_edit->setFixedHeight((URL_INPUT_SIZE));
        history_layout->addWidget(hist_edit);
        QListWidget *histlist = new QListWidget(history_widget);
        history_layout->addWidget(histlist);

        histlist->setStyleSheet("border-radius: 10px 10px 0 0;");
        QObject::connect(hist_edit, &QLineEdit::textChanged, [=]() {
                get_history_matches(view, histlist, hist_edit->text());
        });

        QObject::connect(hist_edit, &QLineEdit::returnPressed, [=]() {
                if (histlist->count() <= 0) return;
                open_url(view, histlist->item(0)->text());
                history_widget->hide();
                hist_edit->clear();
        });

        // toggle search bar
        QShortcut *shortcut = new QShortcut(QKeySequence(url_input_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [&]() {
                if (floating->isVisible())
                        floating->hide();
                else {
                        floating->move(
                        (window->width() - floating->width()) / 2,
                        (window->height() - floating->height()) / 2);
                        floating->show();
                        line_edit->setText(url_element->text());
                        line_edit->selectAll();
                        line_edit->setFocus();
                }
        });

        // toggle history
        QShortcut *hist_shortcut = new QShortcut(QKeySequence(history_toggle_key), window);
        QObject::connect(hist_shortcut, &QShortcut::activated, [&]() {
                if (history_widget->isVisible())
                        history_widget->hide();
                else {
                        history_widget->move(
                        (window->width() - history_widget->width()) / 2,
                        (window->height() - history_widget->height()) / 2);
                        get_history_matches(view, histlist, "");
                        history_widget->show();
                        hist_edit->setText("");
                        hist_edit->setFocus();
                }
        });


        /* Just accept a url as the unique argument */
        if (argc == 2) open_url(view, argv[1]);


        return app.exec();
}
