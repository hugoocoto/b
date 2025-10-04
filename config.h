const char *search_engine = "https://www.google.com/search";
const char *startup_page = NULL; // use a blank page on startup
const char *default_url_text = "This is the url bar";
const char* searchbox_label = "Just a random message to fill this empty space";
const char *url_input_toggle_key = "Ctrl+L";
const char *history_toggle_key = "Ctrl+H";
const char *font_family = "Iosevka NFM";
const int font_pxsize = 20;
const int urlbar_position = BOTTOM; // TOP or BOTTOM
const char *urlbar_toggle_key = "Ctrl+t";
#define GLANGLE // Use gl-angle instead of vulkan
// #undef GLANGLE // Uncomment to use vulkan backend

#define URLBAR_HEIGHT 40
#define URL_INPUT_SIZE 600, 300
#define URL_INPUT_MARGIN 10, 10, 10, 10
#define URL_INPUT_SPACING 0
#define URL_BAR_MARGIN 0, 0, 0, 0
#define URL_BAR_SPACING 0
#define TEXT_MARGIN 10, 0, 10, 0
#define HIST_LAYOUT_MARGIN 10, 10, 10, 10
#define HIST_LAYOUT_SPACING 10
#define HIST_WINDOW_SIZE 600, 300
#define TEXT_INPUT_HEIGHT 40

#define BG_COLOR "#272e33"
#define FG_COLOR "#bbc0b0"
#define BLACK "#383f44"
#define RED "#e67e80"
#define GREEN "#a7c080"
#define YELLOW "#dbbc7f"
#define BLUE "#7fbbb3"
#define MAGENTA "#d699b6"
#define CYAN "#83c092"
#define WHITE "#bbc0b0"
#define TRANSPARENT "00000000"
#define DARK_BLACK "#161d22"

const char *PAGE_BGCOLOR = DARK_BLACK;

const char *URLBAR_STYLE = "color: " FG_COLOR ";"
                           "background-color: " BG_COLOR ";";

const char *URL_INPUT_WINDOW_STYLE = "color: " FG_COLOR ";"
                                     "background-color: " BG_COLOR ";"
                                     "border: 0px;"
                                     "border-radius: 20px;";

const char *INPUT_STYLE = "color: " FG_COLOR ";"
                          "background-color: " BLACK ";"
                          "border: 0px;"
                          "border-radius: 10px;";

const char *HIST_WINDOW_STYLE = "color: " FG_COLOR ";"
                                "background-color: " BG_COLOR ";"
                                "border: 0px;"
                                "border-radius: 20px;";

const char *HIST_INPUT_STYLE = "color: " FG_COLOR ";"
                               "background-color: " BLACK ";"
                               "border: 0px;"
                               "border-radius: 10px;";

const char *HIST_LIST_STYLE = "color: " FG_COLOR ";"
                              "background-color: " BG_COLOR ";"
                              "border: 0;";


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
