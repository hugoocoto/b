/* This file is part of the b browser
 *
 * Copyright (C) 2025  Hugo Coto Flórez
 *
 * b is free software; you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * b is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY of FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Lu. If not, see <https://www.gnu.org/licenses/>
 *
 * For questions or support, contact: me@hugocoto.com
 */

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
#include <QWebEngineView>

enum {
        BOTTOM,
        TOP,
};

#include "config.h"


void
open_url(QWebEngineView *view, QString input)
{
        QUrlQuery query;
        QUrl url;

        if (input.isNull() || input.isEmpty()) return;
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
history_goto_url(QWebEngineView *view, QString url)
{
        QWebEngineHistory *hist = view->history();

        for (QWebEngineHistoryItem item : hist->items()) {
                if (item.url().toString() == url)
                        return hist->goToItem(item);
        }
}

QLabel *
create_urlbar(QWidget *window, QWebEngineView *view, QFont &font)
{
        QLabel *urlbar;

        // URL bar
        urlbar = new QLabel(default_url_text ?: "");
        urlbar->setFixedHeight(URLBAR_HEIGHT);
        urlbar->setFont(font);
        urlbar->setStyleSheet(URLBAR_STYLE);

        // Change urlbar text on urlChanged
        QObject::connect(view->page(), &QWebEnginePage::urlChanged,
                         [=](const QUrl &url) {
                                 urlbar->setMaximumWidth(window->width());
                                 urlbar->setText(url.toString());
                         });

        return urlbar;
}

void
create_url_input(QWidget *window, QWebEngineView *view, QFont font, QLabel *urlbar)
{
        QWidget *widget;
        QVBoxLayout *layout;
        QLineEdit *input;
        QLabel *label;
        QShortcut *shortcut;

        widget = new QWidget(window);
        widget->setFixedSize(URL_INPUT_SIZE);
        widget->setStyleSheet(URL_INPUT_WINDOW_STYLE);
        layout = new QVBoxLayout(widget);
        layout->setContentsMargins(URL_INPUT_MARGIN);
        layout->setSpacing(URL_INPUT_SPACING);
        input = new QLineEdit(widget);
        input->setFont(font);
        input->setTextMargins(TEXT_MARGIN);
        input->setStyleSheet(INPUT_STYLE);
        input->setFixedHeight(TEXT_INPUT_HEIGHT);
        input->setTextMargins(TEXT_MARGIN);
        label = new QLabel(searchbox_label, widget);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(font);
        layout->addWidget(input);
        layout->addWidget(label);

        QObject::connect(input, &QLineEdit::returnPressed, [=]() {
                open_url(view, input->text());
                widget->hide();
                input->clear();
        });

        // toggle search bar
        shortcut = new QShortcut(QKeySequence(url_input_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
                if (widget->isVisible())
                        widget->hide();
                else {
                        widget->move(
                        (window->width() - widget->width()) / 2,
                        (window->height() - widget->height()) / 2);
                        widget->show();
                        input->setText(urlbar->text());
                        input->selectAll();
                        input->setFocus();
                }
        });
}

void
create_hist(QWidget *window, QWebEngineView *view, QFont font)
{
        QWidget *widget;
        QVBoxLayout *layout;
        QLineEdit *input;
        QListWidget *hist_list;
        QShortcut *shortcut;

        widget = new QWidget(window);
        widget->setFixedSize(HIST_WINDOW_SIZE);
        widget->setStyleSheet(HIST_WINDOW_STYLE);
        layout = new QVBoxLayout(widget);
        layout->setContentsMargins(HIST_LAYOUT_MARGIN);
        layout->setSpacing(HIST_LAYOUT_SPACING);
        input = new QLineEdit(widget);
        input->setFont(font);
        input->setTextMargins(TEXT_MARGIN);

        input->setStyleSheet(HIST_INPUT_STYLE);
        input->setFixedHeight(TEXT_INPUT_HEIGHT);
        layout->addWidget(input);
        hist_list = new QListWidget(widget);
        layout->addWidget(hist_list);
        hist_list->setFont(font);
        hist_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        hist_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        hist_list->setStyleSheet(HIST_LIST_STYLE);
        QObject::connect(input, &QLineEdit::textChanged, [=]() {
                get_history_matches(view, hist_list, input->text());
        });

        QObject::connect(input, &QLineEdit::returnPressed, [=]() {
                if (hist_list->count() <= 0) return;
                history_goto_url(view, hist_list->item(0)->text());
                widget->hide();
                input->clear();
        });

        // toggle history
        shortcut = new QShortcut(QKeySequence(history_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
                if (widget->isVisible())
                        widget->hide();
                else {
                        widget->move( // todo: create resize handler
                        (window->width() - widget->width()) / 2,
                        (window->height() - widget->height()) / 2);
                        get_history_matches(view, hist_list, "");
                        widget->show();
                        input->setText("");
                        input->setFocus();
                }
        });

        // go back in history
        shortcut = new QShortcut(QKeySequence(history_back_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
                QWebEngineHistory *h = view->history();
                if (h->canGoBack())
                        h->back();
        });

        // go forward in history
        shortcut = new QShortcut(QKeySequence(history_forward_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
                QWebEngineHistory *h = view->history();
                if (h->canGoForward())
                        h->forward();
        });
}

void
create_main_layout(QWidget *window, QWebEngineView *view, QLabel *urlbar)
{
        QVBoxLayout *layout;

        // Main window layout
        layout = new QVBoxLayout(window);
        layout->setContentsMargins(URL_BAR_MARGIN);
        layout->setSpacing(URL_BAR_SPACING);

        switch (urlbar_position) {
        case TOP:
                layout->addWidget(urlbar);
                layout->addWidget(view);
                break;
        case BOTTOM:
                layout->addWidget(view);
                layout->addWidget(urlbar);
                break;
        }

        QShortcut *shortcut = new QShortcut(QKeySequence(urlbar_toggle_key), window);
        QObject::connect(shortcut, &QShortcut::activated, [=]() {
                if (urlbar->isVisible())
                        urlbar->hide();
                else
                        urlbar->show();
        });
}

int
main(int argc, char *argv[])
{
        QWebEngineView *view;
        QWidget *window;
        QWebEngineProfile *profile;
        QWebEnginePage *page;
        QFont font;
        QLabel *urlbar;

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
        qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--use-gl=angle "
                                              "--use-angle=gl "
                                              "--enable-gpu-rasterization "
                                              "--enable-zero-copy "
                                              "--ignore-gpu-blocklist");
#endif

        QApplication app(argc, argv);

        // cookies
        profile = new QWebEngineProfile(QString::fromLatin1("b.%1").arg(qWebEngineChromiumVersion()));
        page = new QWebEnginePage(profile);
        page->setBackgroundColor(QColor(PAGE_BGCOLOR));

        // Content
        view = new QWebEngineView();
        view->setPage(page);

        // font
        font = QFont(font_family);
        font.setPixelSize(font_pxsize);

        // Main window
        window = new QWidget;
        window->show();

        urlbar = create_urlbar(window, view, font);

        // View + url main layout
        create_main_layout(window, view, urlbar);

        // history widget
        create_hist(window, view, font);

        // Url user modification widget
        create_url_input(window, view, font, urlbar);

        open_url(view, argc == 2 ? argv[1] : startup_page);

        return app.exec();
}
