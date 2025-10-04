/* Feel */
const char *search_engine = "https://www.google.com/search";
const char *startup_page = NULL; // use a blank page on startup

/* Mappings */
const char *url_input_toggle_key = "Ctrl+L";
const char *history_toggle_key = "Ctrl+H";
const char *history_forward_key = "Ctrl+]";
const char *history_back_key = "Ctrl+[";
const char *urlbar_toggle_key = "Ctrl+T";
const char *history_restore = "Ctrl+Shift+H";

/* Fonts */
const char *font_family = "Iosevka NFM";
const int font_pxsize = 20;

/* Ui */
const int urlbar_position = BOTTOM; // TOP or BOTTOM

/* Random messages */
const char *default_url_text = "This is the url bar";
const char *searchbox_label = "Just a random message to fill this empty space";

// Enable this if you notice that pictures and videos renders too slow (for
// example when using google images tab) It's enabled by default because I have
// problems with vulkan backend but it should perform better.
#define GLANGLE // Use gl-angle instead of vulkan
// #undef GLANGLE // Uncomment to use vulkan backend

#define AUTO_LOAD_HISTORY  // Load history on startup
#define PERSISTENT_HISTORY // Store history between sessions
#undef AUTO_LOAD_HISTORY
// #undef PERSISTENT_HISTORY

#define URLBAR_HEIGHT 40
#define URL_INPUT_SIZE 600, 300
#define URL_INPUT_MARGIN 10, 10, 10, 10
#define URL_INPUT_SPACING 10
#define URL_BAR_MARGIN 0, 0, 0, 0
#define URL_BAR_SPACING 0
#define TEXT_MARGIN 10, 0, 10, 0
#define HIST_LAYOUT_MARGIN 10, 10, 10, 10
#define HIST_LAYOUT_SPACING 10
#define HIST_WINDOW_SIZE 600, 300
#define TEXT_INPUT_HEIGHT 40

#define LIGHT_WHITE "#f8f9fa"
#define BASE_WHITE "#e9ecef"
#define DARK_WHITE "#dee2e6"
#define LIGHT_GRAY "#ced4da"
#define BASE_GRAY "#adb5bd"
#define DARK_GRAY "#6c757d"
#define LIGHT_BLACK "#495057"
#define BASE_BLACK "#343a40"
#define DARK_BLACK "#212529"
#define TRANSPARENT "#00000000"

const char *PAGE_BGCOLOR = LIGHT_BLACK;

const char *URLBAR_STYLE = "color: " BASE_WHITE ";"
                           "background-color: " BASE_BLACK ";";

const char *URL_INPUT_WINDOW_STYLE = "color: " LIGHT_WHITE ";"
                                     "background-color: " DARK_BLACK ";"
                                     "border: 0px;"
                                     "border-radius: 20px;";

const char *INPUT_STYLE = "color: " LIGHT_WHITE ";"
                          "background-color: " LIGHT_BLACK ";"
                          "border: 0px;"
                          "border-radius: 10px;";

const char *INPUT_SEARCHBOX_STYLE = "color: " DARK_WHITE ";"
                                    "background-color: " BASE_BLACK ";"
                                    "border: 0;"
                                    "border-radius: 10px;";

const char *HIST_WINDOW_STYLE = "background-color: " DARK_BLACK ";"
                                "border: 0px;"
                                "border-radius: 20px;";

const char *HIST_INPUT_STYLE = "color: " LIGHT_WHITE ";"
                               "background-color: " LIGHT_BLACK ";"
                               "border: 0px;"
                               "border-radius: 10px;";

const char *HIST_LIST_STYLE = "color: " DARK_WHITE ";"
                              "background-color: " BASE_BLACK ";"
                              "border: 0;"
                              "border-radius: 10px;";


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
