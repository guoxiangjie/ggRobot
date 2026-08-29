#!/bin/bash

curl -i \
    -H 'content-type:application/json' \
    -X POST 'http://127.0.0.1:51822/rpc/aimrt.protocols.time_manipulator_plugin.TimeManipulatorService/Pause' \
    -d '{"executor_name": "time_schedule_executor"}'
