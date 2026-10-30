// Simple helper header to ensure pico libs support ?BT

#if !defined(ENABLE_CLASSIC) && !defined(ENABLE_BLE)
#error "This library needs Bluetooth enabled. Use the 'Tools->IP/Bluetooth Stack' menu in the IDE to enable it."
#endif
