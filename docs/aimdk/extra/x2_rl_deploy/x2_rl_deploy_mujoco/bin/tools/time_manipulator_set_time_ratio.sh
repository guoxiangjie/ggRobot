#!/bin/bash

time_ratio=$1

if [ -z "$time_ratio" ]; then
    time_ratio=0.5
fi

curl -i \
    -H 'content-type:application/json' \
    -X POST 'http://127.0.0.1:51822/rpc/aimrt.protocols.time_manipulator_plugin.TimeManipulatorService/SetTimeRatio' \
    -d '{"executor_name": "time_schedule_executor", "time_ratio": '$time_ratio'}'
