# ROM source patches

color="\033[0;32m"
end="\033[0m"

echo -e "${color}Applying patches${end}"
sleep 1

# Remove pixel headers to avoid conflicts
rm -rf hardware/google/pixel/kernel_headers/Android.bp

# Remove hardware/lineage/compat to avoid conflicts
rm -rf hardware/lineage/compat/Android.bp

# Clone kernel/vendortree/xiaomi-hardware
echo -e "${color}Setup kernel,vendor,xiaomi-hardware tree ${end}"
git clone https://github.com/muralivijay/kernel_xiaomi_sm6225.git -b main kernel/xiaomi/sm6225
git clone https://github.com/muralivijay/android_vendor_xiaomi_spes.git -b 13.0 vendor/xiaomi/spes
git clone https://github.com/LineageOS/android_hardware_xiaomi.git -b lineage-20 hardware/xioami/

# Clone Miuicamera
echo -e "${color}Setup Miuicamera ${end}"
git clone https://gitlab.com/ThankYouMario/proprietary_vendor_xiaomi_camera.git -b uvite-sm6225 vendor/xiaomi/camera/
