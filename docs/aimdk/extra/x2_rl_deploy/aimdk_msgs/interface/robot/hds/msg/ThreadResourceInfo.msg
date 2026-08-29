# 线程ID
uint64 thread_id

# 线程名称
string thread_name

# 当前线程cpu使用率
float64 cpu_usage_ratio

# 当前进程调度策略
string cpu_sched_policy

# 当前进程调度优先级
int32 cpu_sched_priority

int32[] bounding_cpus  # 当前进程绑定cpu
