uint8 value

uint8 IN_INITIAL = 0         # 起始态
uint8 IN_READY = 1           # 就绪态，可执行业务
uint8 IN_MOVE = 2            # 迁移态，不可执行业务，拒绝迁移请求
uint8 IN_ROLLBACK = 3        # 回滚态，不可执行业务，拒绝迁移请求
uint8 IN_FALLBACK = 4        # 异常态，接收迁移请求
uint8 IN_FALLBACK_MOVE = 5   # 异常迁移态，不可执行业务，拒绝迁移请求