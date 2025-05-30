// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 8.3.11
// Project name: Arnobot_GroundStation

#include "ui.h"

void ui_start_screen_init(void)
{
ui_start = lv_obj_create(NULL);
lv_obj_clear_flag( ui_start, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_header3 = ui_header_create(ui_start);
lv_obj_set_x( ui_header3, -2 );
lv_obj_set_y( ui_header3, -209 );

ui_logo1 = lv_img_create(ui_start);
lv_img_set_src(ui_logo1, &ui_img_horizontal_png);
lv_obj_set_width( ui_logo1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_logo1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_logo1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_logo1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_logo1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Status3 = lv_obj_create(ui_start);
lv_obj_remove_style_all(ui_Status3);
lv_obj_set_width( ui_Status3, 309);
lv_obj_set_height( ui_Status3, 69);
lv_obj_set_x( ui_Status3, 8 );
lv_obj_set_y( ui_Status3, 183 );
lv_obj_set_align( ui_Status3, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Status3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Status3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Status3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_groundstationIndicator = lv_obj_create(ui_Status3);
lv_obj_set_width( ui_groundstationIndicator, 48);
lv_obj_set_height( ui_groundstationIndicator, 47);
lv_obj_set_x( ui_groundstationIndicator, -112 );
lv_obj_set_y( ui_groundstationIndicator, 3 );
lv_obj_set_align( ui_groundstationIndicator, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_groundstationIndicator, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_groundstationIndicator, 50, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_groundstationIndicator, lv_color_hex(0x25FF09), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_groundstationIndicator, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_groundstationStatus = lv_label_create(ui_Status3);
lv_obj_set_width( ui_groundstationStatus, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_groundstationStatus, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_groundstationStatus, 41 );
lv_obj_set_y( ui_groundstationStatus, 3 );
lv_obj_set_align( ui_groundstationStatus, LV_ALIGN_CENTER );
lv_label_set_text(ui_groundstationStatus,"BOT Connected");
lv_obj_set_style_text_font(ui_groundstationStatus, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_logo1, ui_event_logo1, LV_EVENT_ALL, NULL);

}
