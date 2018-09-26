﻿#include "gtest/gtest.h"
#include "text_selector/text_selector.h"

#include <string>

using std::string;

TEST(TextSelector, basic) {
  value_t v1;
  value_t v2;
  widget_t* w = text_selector_create(NULL, 10, 20, 30, 40);
  text_selector_t* text_selector = TEXT_SELECTOR(w);

  ASSERT_EQ(text_selector_append_option(w, 0, "000"), RET_OK);
  ASSERT_EQ(text_selector_append_option(w, 111, "111"), RET_OK);
  ASSERT_EQ(text_selector_append_option(w, 222, "222"), RET_OK);
  ASSERT_EQ(text_selector_append_option(w, 233, "333"), RET_OK);

  value_set_int(&v1, 1);
  ASSERT_EQ(widget_set_prop(w, WIDGET_PROP_SELECTED_INDEX, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(w, WIDGET_PROP_SELECTED_INDEX, &v2), RET_OK);
  ASSERT_EQ(value_int(&v1), value_int(&v2));
  ASSERT_EQ(value_int(&v1), text_selector->selected_index);
  ASSERT_EQ(text_selector_get_value(w), 111);
  ASSERT_EQ(string(text_selector_get_text(w)), string("111"));

  value_set_int(&v1, 3);
  ASSERT_EQ(widget_set_prop(w, TEXT_SELECTOR_PROP_VISIBLE_NR, &v1), RET_OK);
  ASSERT_EQ(value_int(&v1), text_selector->visible_nr);

  /*not eq 3, set it to 5*/
  value_set_int(&v1, 4);
  ASSERT_EQ(widget_set_prop(w, TEXT_SELECTOR_PROP_VISIBLE_NR, &v1), RET_OK);
  ASSERT_EQ(5, text_selector->visible_nr);

  value_set_int(&v1, 5);
  ASSERT_EQ(widget_set_prop(w, TEXT_SELECTOR_PROP_VISIBLE_NR, &v1), RET_OK);
  ASSERT_EQ(value_int(&v1), text_selector->visible_nr);

  widget_destroy(w);
}

TEST(TextSelector, options) {
  widget_t* w = text_selector_create(NULL, 10, 20, 30, 40);

  ASSERT_EQ(text_selector_count_options(w), 0);
  ASSERT_EQ(text_selector_append_option(w, 1, "red"), RET_OK);
  ASSERT_EQ(text_selector_count_options(w), 1);

  ASSERT_EQ(text_selector_append_option(w, 2, "green"), RET_OK);
  ASSERT_EQ(text_selector_count_options(w), 2);

  ASSERT_EQ(text_selector_append_option(w, 3, "blue"), RET_OK);
  ASSERT_EQ(text_selector_count_options(w), 3);

  text_selector_set_selected_index(w, 0);
  ASSERT_EQ(text_selector_get_value(w), 1);
  ASSERT_EQ(string(text_selector_get_text(w)), string("red"));

  text_selector_set_selected_index(w, 1);
  ASSERT_EQ(text_selector_get_value(w), 2);
  ASSERT_EQ(string(text_selector_get_text(w)), string("green"));

  text_selector_reset_options(w);
  ASSERT_EQ(text_selector_count_options(w), 0);

  widget_destroy(w);
}

TEST(TextSelector, parse_options) {
  widget_t* w = text_selector_create(NULL, 10, 20, 30, 40);

  text_selector_parse_options(w, "1:red;2:green;3:blue");
  ASSERT_EQ(text_selector_count_options(w), 3);

  text_selector_set_selected_index(w, 0);
  ASSERT_EQ(text_selector_get_value(w), 1);
  ASSERT_EQ(string(text_selector_get_text(w)), string("red"));

  text_selector_set_selected_index(w, 1);
  ASSERT_EQ(text_selector_get_value(w), 2);
  ASSERT_EQ(string(text_selector_get_text(w)), string("green"));

  text_selector_reset_options(w);
  ASSERT_EQ(text_selector_count_options(w), 0);

  widget_destroy(w);
}

TEST(TextSelector, props) {
  value_t v1;
  value_t v2;
  const char* str = "1:red;2:green;3:blue";
  widget_t* w = text_selector_create(NULL, 10, 20, 30, 40);

  value_set_str(&v1, str);
  ASSERT_EQ(text_selector_cast(w), w);
  ASSERT_EQ(widget_set_prop(w, WIDGET_PROP_OPTIONS, &v1), RET_OK);
  ASSERT_EQ(widget_get_prop(w, WIDGET_PROP_OPTIONS, &v2), RET_OK);
  ASSERT_EQ(string(value_str(&v2)), string(str));
  ASSERT_EQ(text_selector_count_options(w), 3);

  widget_destroy(w);
}
