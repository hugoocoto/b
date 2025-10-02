const char *search_engine = "https://www.google.com/search";
const char *startup_page = NULL;
const char *default_url_text = "This is the url bar";
const char *url_input_toggle_key = "Ctrl+L";
#define URLBAR_HEIGHT 40
#define URL_INPUT_SIZE 600, 40
#define URL_INPUT_MARGIN 0, 0, 0, 0
#define URL_INPUT_SPACING 0
#define URL_BAR_MARGIN 0, 0, 0, 0
#define URL_BAR_SPACING 0
#define TEXT_MARGIN 10, 0, 10, 0
const char *font_family = "Iosevka NFM";
const int font_pxsize = 20;

#define GLANGLE // Use gl-angle instead of vulkan
// #undef GLANGLE // Uncomment to use vulkan backend


#define BG_COLOR "#272e33"
#define FG_COLOR "#bbc0b0"
#define BLACK "#859289"
#define RED "#e67e80"
#define GREEN "#a7c080"
#define YELLOW "#dbbc7f"
#define BLUE "#7fbbb3"
#define MAGENTA "#d699b6"
#define CYAN "#83c092"
#define WHITE "#bbc0b0"

const char *URLBAR_STYLE = "color: " FG_COLOR ";"
                           "background-color: " BG_COLOR ";"
                           "border-left:   1px solid " BLACK ";"
                           "border-top:    1px solid " BLACK ";"
                           "border-right:  1px solid " BLACK ";"
                           "border-bottom: 3px solid " BLACK ";";

const char *INPUT_STYLE = "color: " FG_COLOR ";"
                          "border-radius: 10px;"
                          "background-color: " BG_COLOR ";"
                          "border: 3px solid " BLACK ";";
