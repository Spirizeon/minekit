#!/bin/bash
# Uninstall kmod_launcher
# Usage: sudo ./uninstall.sh

if [ "$EUID" -ne 0 ]; then 
  echo "Please run as root (sudo)"
  exit
fi

echo "1. Removing auto-load configuration..."
# This file tells systemd to load the module on boot
rm -f /etc/modules-load.d/kmod_launcher.conf

echo "2. Removing kernel module file..."
# This is the actual installed binary
rm -f /lib/modules/$(uname -r)/kernel/drivers/misc/kmod_launcher.ko

echo "3. Updating module dependencies..."
# Refresh the list of available modules
depmod -a

echo "4. Unloading module from current session (if active)..."
# Try to unload it from the running kernel. 
# It might fail if not loaded, so we silence errors with 2>/dev/null
rmmod kmod_launcher 2>/dev/null

echo "Success. The module is removed and will not run on the next boot."
