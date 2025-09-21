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
git clone --depth=1 https://github.com/muralivijay/kernel_xiaomi_sm6225.git -b main kernel/xiaomi/spes
git clone --depth=1 https://github.com/muralivijay/android_vendor_xiaomi_spes.git -b 13.0 vendor/xiaomi/spes
git clone --depth=1 https://github.com/LineageOS/android_hardware_xiaomi.git -b lineage-20 hardware/xiaomi

# GcamBSG
echo -e "${color}Setup gcamBSG ${end}"

read -p "Do you want to enable GCam support? (yes/no): " USER_INPUT

if [[ "$USER_INPUT" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    export ENABLE_GCAM=true
    echo "GCam support enabled."
    echo "Cloning GCam source..."
    git clone --depth=1 https://gitlab.com/GustavoMends/vendor_GoogleCamera.git -b sg vendor/GoogleCamera
else
    export ENABLE_GCAM=false
    echo "GCam support disabled. Skipping or Removing if GCam source exits."
    rm -rf vendor/GoogleCamera
fi
