dmesg -C

while [[ 1 -le 2 ]]; do
	if [[ $(dmesg | tail | grep "usb") ]]; then
		if [[ $(dmesg | tail | grep "disconnect") ]]; then
			echo "USB disconnected"
		else
			echo "USB connected"
			sleep 1
			dmesg -C
		fi
		dmesg -C
	fi
done
