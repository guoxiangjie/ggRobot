# Request
CommonRequest request

# 来源追踪
string trace_id

# 灯带模式
uint8 led_strip_mode

## led_strip_mode: 灯带模式枚举
uint8 LED_STRIP_MODE_CONSTANT = 0 # 常亮
uint8 LED_STRIP_MODE_BREATH = 1   # 呼吸，4s周期，亮度正弦变化
uint8 LED_STRIP_MODE_FLASH = 2    # 闪烁，1s周期，0.5s亮，0.5s灭
uint8 LED_STRIP_MODE_FLOW = 3     # 流水，2s周期，从左到右依次点亮，然后灭
uint8 LED_STRIP_MODE_MAX = 4      # 无效

# 红色分量
uint8 r

# 绿色分量
uint8 g

# 蓝色分量
uint8 b

# 优先级
int32 priority

# 优先级重置标志
bool reset_priority

