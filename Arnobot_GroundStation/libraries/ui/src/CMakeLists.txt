SET(SOURCES ui_comp_header.c
    ui_comp.c
    ui_start.c
    ui_dashboard.c
    ui_stats.c
    ui_altius.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_icon_colour_digital_png.c
    ui_img_horizontal_png.c
    ui_img_image_png.c)

add_library(ui ${SOURCES})
