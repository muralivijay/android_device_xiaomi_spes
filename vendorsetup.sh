# ROM source patches

color="\033[0;32m"
end="\033[0m"

echo -e "${color}Applying patches${end}"
sleep 1

# Remove pixel headers to avoid conflicts
rm -rf hardware/google/pixel/kernel_headers/Android.bp

# Kernel & Vendor Sources
git clone --depth=1 https://github.com/muralivijay/android_vendor_xiaomi_spes.git -b 16-QPR2 vendor/xiaomi/spes
git clone --depth=1 https://github.com/muralivijay/kernel_xiaomi_spes -b main-a16-sm8250-base kernel/xiaomi/sm6225

# Hardware/Xiaomi
rm -fr hardware/xiaomi
git clone https://github.com/LineageOS/android_hardware_xiaomi hardware/xiaomi
rm -fr hardware/lineage/interfaces/health/aidl/default/Android.bp
rm -fr hardware/xiaomi/interfaces/xiaomi/hardware/mtdservice/1.3
rm -fr hardware/xiaomi/interfaces/xiaomi/hardware/mfidoca/1.0

# HALS
echo -e "${color}cloning audio HAL ${end}"
rm -rf hardware/qcom-caf/sm8250/audio
git clone https://github.com/muralivijay/android_hardware_qcom_audio.git -b lineage-23.2-caf-sm8250 hardware/qcom-caf/sm8250/audio

echo -e "${color}cloning display HAL ${end}"
rm -rf hardware/qcom-caf/sm8250/display
git clone https://github.com/muralivijay/android_hardware_qcom_display.git -b lineage-23.2-caf-sm8250 hardware/qcom-caf/sm8250/display

# Sepolicy fix for imsrcsd
echo -e "${color}Switch back to legacy imsrcsd sepolicy${end}"
rm -rf device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/ims/imsservice.te
cp device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/legacy-ims/hal_rcsservice.te device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/ims/hal_rcsservice.te

# Rename conflicting qti_kernel_headers in source
sed -i 's/"qti_kernel_headers"/"qti_kernel_headers_old"/g' vendor/lineage/build/soong/Android.bp
