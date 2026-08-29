#!/usr/bin/env python3
"""
System State Migrator - Synchronous Python version
"""

import sys
import time
import rclpy
from rclpy.node import Node
import aimdk_msgs.srv as aimdk_srv
import aimdk_msgs.msg as aimdk_msg


class SyncSystemStateMigrator(Node):
    """Synchronous version of system state migrator"""

    def __init__(self, target_state: str):
        super().__init__('sync_system_state_migrator')
        self.target_state = target_state

        # Create service clients
        self.migrate_client = self.create_client(
            aimdk_srv.MigrateSystemState,
            '/aimdk_5Fmsgs/srv/MigrateSystemState'
        )

        self.get_state_client = self.create_client(
            aimdk_srv.GetSystemState,
            '/aimdk_5Fmsgs/srv/GetSystemState'
        )

        self.get_logger().info(f'Target state: {self.target_state}')

    def wait_for_services(self, timeout_sec: float = 30.0) -> bool:
        """Wait for services to become available"""
        self.get_logger().info('Waiting for services...')

        start_time = time.time()
        while time.time() - start_time < timeout_sec and rclpy.ok():
            if (self.migrate_client.wait_for_service(timeout_sec=1.0) and
                    self.get_state_client.wait_for_service(timeout_sec=1.0)):
                self.get_logger().info('Services are available')
                return True

            self.get_logger().info('Services not available, waiting...')
            time.sleep(0.5)

        self.get_logger().error(
            f'Timeout waiting for services after {timeout_sec} seconds')
        return False

    def migrate_state_sync(self, max_retries: int = 5, timeout_sec: float = 30.0) -> bool:
        """Send migration request synchronously with retry"""
        request = aimdk_srv.MigrateSystemState.Request()
        now = self.get_clock().now()
        request.header.header.stamp.sec = now.nanoseconds // 1_000_000_000
        request.header.header.stamp.nanosec = now.nanoseconds % 1_000_000_000
        request.state = self.target_state

        for attempt in range(1, max_retries + 1):
            self.get_logger().info(
                f'Sending migration request to {self.target_state} '
                f'(attempt {attempt}/{max_retries})...'
            )

            future = None
            try:
                future = self.migrate_client.call_async(request)

                start_time = time.time()
                while rclpy.ok() and time.time() - start_time < timeout_sec:
                    rclpy.spin_once(self, timeout_sec=0.1)
                    if future.done():
                        response = future.result()
                        if response.header.status.value == aimdk_msg.CommonState.SUCCESS:
                            self.get_logger().info('Migration request accepted')
                            return True
                        else:
                            self.get_logger().error(
                                f'Migration failed: {response.header.message}'
                            )
                            return False

                self.get_logger().warning(
                    f'Timeout waiting for migration response '
                    f'(attempt {attempt}/{max_retries})'
                )

            except Exception as e:
                self.get_logger().error(
                    f'Migration service call failed (attempt {attempt}/{max_retries}): {e}'
                )
            finally:
                if future is not None and not future.done():
                    future.cancel()

            if attempt < max_retries:
                self.get_logger().info('Retrying migration request in 2.0 seconds...')
                time.sleep(2.0)

        self.get_logger().error(
            f'Migration request failed after {max_retries} attempts'
        )
        return False

    def get_current_state_sync(self, max_retries: int = 3, timeout_sec: float = 10.0):
        """Get current system state synchronously with retry"""
        request = aimdk_srv.GetSystemState.Request()
        now = self.get_clock().now()
        request.header.header.stamp.sec = now.nanoseconds // 1_000_000_000
        request.header.header.stamp.nanosec = now.nanoseconds % 1_000_000_000

        for attempt in range(1, max_retries + 1):
            future = None
            try:
                future = self.get_state_client.call_async(request)

                start_time = time.time()
                while rclpy.ok() and time.time() - start_time < timeout_sec:
                    rclpy.spin_once(self, timeout_sec=0.1)
                    if future.done():
                        return future.result()

                self.get_logger().warning(
                    f'Timeout getting system state (attempt {attempt}/{max_retries})'
                )

            except Exception as e:
                self.get_logger().error(
                    f'GetSystemState service call failed (attempt {attempt}/{max_retries}): {e}'
                )
            finally:
                if future is not None and not future.done():
                    future.cancel()

            if attempt < max_retries:
                time.sleep(1.0)

        self.get_logger().error(
            f'Failed to get system state after {max_retries} attempts'
        )
        return None

    def monitor_migration_sync(self, max_checks: int = 300) -> bool:
        """Monitor migration progress synchronously"""
        self.get_logger().info('Monitoring migration progress...')

        check_count = 0
        start_time = time.time()

        while check_count < max_checks and rclpy.ok():
            # Wait between checks
            time.sleep(1.0)

            # Check current state
            response = self.get_current_state_sync()
            if response is None:
                self.get_logger().warning('Failed to get system state, will retry...')
                continue

            check_count += 1

            # Check if migration is complete
            current_state_lower = response.cur_state.lower()
            target_state_lower = self.target_state.lower()

            state_match = (current_state_lower == target_state_lower)
            status_match = (response.curr_status.value ==
                            aimdk_msg.SystemStatus.IN_READY)

            self.get_logger().info(
                f'Check {check_count}: State="{response.cur_state}" '
                f'(match={state_match}), Status={response.curr_status.value} (match={status_match})'
            )

            if state_match and status_match:
                self.get_logger().info(
                    f'Migration to {self.target_state} completed successfully!')
                return True

            # Check timeout
            if time.time() - start_time > 300.0:  # 5 minutes total timeout
                self.get_logger().error('Migration timeout after 5 minutes')
                return False

        self.get_logger().error(f'Migration failed after {max_checks} checks')
        return False

    def run_migration(self) -> bool:
        """Run complete migration process"""
        # Step 1: Wait for services
        if not self.wait_for_services():
            return False

        # Step 2: Send migration request
        if not self.migrate_state_sync():
            return False

        # Step 3: Monitor migration progress
        return self.monitor_migration_sync()


def main():
    """
    Main function
    """
    # Check command line arguments
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <target_state>')
        print('\nAvailable target states: Ready, Develop_Nav, Develop_Audio_Linux, Develop_Audio_ROS, Develop_MC')
        return 1

    # Get target state from command line argument
    target_state = sys.argv[1]

    # Validate target state
    if not target_state:
        print('Error: Target state cannot be empty', file=sys.stderr)
        return 1

    # Initialize ROS2
    rclpy.init()

    result = 1
    node = None

    try:
        # Create migrator node
        node = SyncSystemStateMigrator(target_state)

        # Run migration
        if node.run_migration():
            print(f'\nMigration to {target_state} completed successfully!')
            result = 0
        else:
            print(f'\nMigration to {target_state} failed')
            result = 1

    except KeyboardInterrupt:
        print('\nProgram interrupted by user')
        result = 1
    except Exception as e:
        print(f'Error: {e}', file=sys.stderr)
        result = 1
    finally:
        # Cleanup
        if node:
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

    return result


if __name__ == '__main__':
    sys.exit(main())
