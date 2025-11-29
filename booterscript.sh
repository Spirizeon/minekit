sudo cp kmod_launcher.ko /lib/modules/$(uname -r)/kernel/drivers/misc/
sudo depmod -a
echo "kmod_launcher" | sudo tee /etc/modules-load.d/kmod_launcher.conf
reboot
