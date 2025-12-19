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
echo -e "${color}Setup LeicaCamera ${end}"
read -p "Do you want to enable LeicaCamera support? (yes/no): " USER_INPUT

if [[ "$USER_INPUT" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    export ENABLE_LEICACAM=true
    echo "Leicacamera support enabled."
    echo "Cloning GCam source..."
    git clone --depth=1 https://gitlab.com/muralivijay/android-vendor-xiaomi-spes-leicacamera.git -b main vendor/xiaomi/spes-leicacamera
else
    export ENABLE_LEICACAM=false
    echo "Leicacamera support disabled. Skipping or Removing Leicacamera source if exits."
    rm -rf vendor/xiaomi/spes-leicacamera
fi

# Gapps
echo -e "${color}Setup Gapps ${end}"
read -p "Do you want to build with gapps support? (yes/no): " USER_INPUT

if [[ "$USER_INPUT" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    echo "Gapps support enabled."
    echo "Cloning gapps source from crdroid gitlab..."
    git clone --depth=1 https://gitlab.com/crdroidandroid/android-vendor-gapps-spes.git -b 13.0 vendor/gapps
else
    echo "Gapps support disabled. Skipping ..."
    rm -rf vendor/gapps
fi
