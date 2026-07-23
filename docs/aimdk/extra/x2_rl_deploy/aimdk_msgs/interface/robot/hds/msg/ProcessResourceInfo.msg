# 进程ID
uint64 process_id

# 进程名称
string process_name

# 当前进程内存使用量(kb)
uint64 process_mem_usage

# 当前进程内存使用率
float64 process_mem_usage_ratio

# 当前进程cpu使用率
float64 process_cpu_usage_ratio

# 当前进程线程数
uint64 thread_count

ThreadResourceInfo[] threads