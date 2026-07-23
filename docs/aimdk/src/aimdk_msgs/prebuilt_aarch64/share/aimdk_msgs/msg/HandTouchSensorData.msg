# 手心手背的触摸传感器数据 5*5, 数组长度一般是25, 雷赛是36，但是雷赛没有手背
uint8[36] palm_touch_data
uint8[36] back_of_hand_touch_data

# 指尖触摸传感器数据 4*4, 数组长度一般是16, Omnihands 长度是16，雷赛是12
uint8[16] thumb_touch_data
uint8[16] index_finger_touch_data
uint8[16] middle_finger_touch_data
uint8[16] ring_finger_touch_data
uint8[16] little_finger_touch_data
