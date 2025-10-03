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

        list->clear();
        for (QWebEngineHistoryItem item : hist->items()) {
                if (match.isEmpty() || item.url().toString().contains(match))
                        list->addItem(item.url().toString());
        }
}

void
create_url_input(QWidget *window, QWebEngineView *view, QFont font, QLabel *url_element)
{
        QWidget *floating;
        QVBoxLayout *floating_layout;
        QLineEdit *line_edit;

        floating = new QWidget(window);
        floating->setFixedSize(URL_INPUT_SIZE);
        floating->setStyleSheet(URL_INPUT_WINDOW_STYLE);
        floating_layout = new QVBoxLayout(floating);
        floating_layout->setContentsMargins(URL_INPUT_MARGIN);
        floating_layout->setSpacing(URL_INPUT_SPACING);
        line_edit = new QLineEdit(floating);
        line_edit->setFont(font);
        line_edit->setTextMargins(TEXT_MARGIN);
        line_edit->setStyleSheet(INPUT_STYLE);
        line_edit->setFixedHeight(TEXT_INPUT_HEIGHT);
        line_edit->setTextMargins(TEXT_MARGIN);
        QLabel *label = new QLabel("Just some random message to fill this empty space", floating);
        label->setFont(font);
        floating_layout->addWidget(line_edit);
        floating_layout->addWidget(label);

        QObject::connect(line_edit, &QLineEdit::returnPressed, [=]() {
                open_url(view, line_edit->text());
                floating->hide();
                line_edit->clear();
        });

        // toggle search bar
        QShortcut *shortcut = new QShortcut(QKeySequence(url_input_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
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
}

void
create_hist(QWidget *window, QWebEngineView *view, QFont font)
{
        QWidget *history_widget;
        QVBoxLayout *history_layout;
        QLineEdit *hist_edit;

        history_widget = new QWidget(window);
        history_widget->setFixedSize(HIST_WINDOW_SIZE);
        history_widget->setStyleSheet(HIST_WINDOW_STYLE);
        history_layout = new QVBoxLayout(history_widget);
        history_layout->setContentsMargins(HIST_LAYOUT_MARGIN);
        history_layout->setSpacing(HIST_LAYOUT_SPACING);
        hist_edit = new QLineEdit(history_widget);
        hist_edit->setFont(font);
        hist_edit->setTextMargins(TEXT_MARGIN);

        hist_edit->setStyleSheet(HIST_INPUT_STYLE);
        hist_edit->setFixedHeight(TEXT_INPUT_HEIGHT);
        history_layout->addWidget(hist_edit);
        QListWidget *histlist = new QListWidget(history_widget);
        history_layout->addWidget(histlist);
        histlist->setFont(font);
        histlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        histlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        histlist->setStyleSheet(HIST_LIST_STYLE);
        QObject::connect(hist_edit, &QLineEdit::textChanged, [=]() {
                get_history_matches(view, histlist, hist_edit->text());
        });

        QObject::connect(hist_edit, &QLineEdit::returnPressed, [=]() {
                if (histlist->count() <= 0) return;
                open_url(view, histlist->item(0)->text());
                history_widget->hide();
                hist_edit->clear();
        });

        // toggle history
        QShortcut *hist_shortcut = new QShortcut(QKeySequence(history_toggle_key), window);
        QObject::connect(hist_shortcut, &QShortcut::activated, [=]() {
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
}

int
main(int argc, char *argv[])
{
        QLabel *url_element;
        QWebEngineView *view;
        QWidget *window;
        QVBoxLayout *layout;
        QWebEngineProfile *profile;
        QWebEnginePage *page;
        QFont font;

        // Show help message before load anything
        if (argc == 2 && !strcmp(argv[1], "--help")) {
                printf("The b browser! By Hugo Coto\n"
                       "Usage: %s [--help, url] -> "
                       "Launch b and open url if provided\n",
                       argv[0]);
                return 0;
        }

#if defined(GLANGLE)
        // just because It doesn't find my vulkan and it's slow as f*ck
        QByteArray flags = "--use-gl=angle --use-angle=gl "
                           "--enable-gpu-rasterization --enable-zero-copy "
                           "--ignore-gpu-blocklist";
        qputenv("QTWEBENGINE_CHROMIUM_FLAGS", flags);
#endif

        QApplication app(argc, argv);

        // cookies
        profile = new QWebEngineProfile(QString::fromLatin1("b.%1").arg(qWebEngineChromiumVersion()));
        page = new QWebEnginePage(profile);

        // Content
        view = new QWebEngineView();
        view->setPage(page);

        // font
        font = QFont(font_family);
        font.setPixelSize(font_pxsize);

        // Main window
        window = new QWidget;
        window->show();

        // URL bar
        url_element = new QLabel(default_url_text ?: "");
        url_element->setFixedHeight(URLBAR_HEIGHT);
        url_element->setFont(font);
        url_element->setStyleSheet(URLBAR_STYLE);

        // Change url_element text on urlChanged
        QObject::connect(view->page(), &QWebEnginePage::urlChanged,
                         [=](const QUrl &url) {
                                 url_element->setMaximumWidth(window->width()); // todo: change this
                                 url_element->setText(url.toString());
                         });

        // Main window layout
        layout = new QVBoxLayout(window);
        layout->addWidget(url_element);
        layout->addWidget(view);
        layout->setContentsMargins(URL_BAR_MARGIN);
        layout->setSpacing(URL_BAR_SPACING);

        // history widget
        create_hist(window, view, font);

        // Url user modification widget
        create_url_input(window, view, font, url_element);

        /* Just accept a url as the unique argument */
        if (argc == 2) open_url(view, argv[1]);
        if (argc != 2 && startup_page) view->setUrl(QUrl(startup_page));

        return app.exec();
}
