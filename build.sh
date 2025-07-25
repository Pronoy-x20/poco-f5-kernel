#!/bin/bash
#

SECONDS=0 # start builtin bash timer
LOG_FILE="log.txt"
# Membersihkan file log sebelumnya di awal eksekusi
> "$LOG_FILE"

KP_ROOT="$(realpath ../..)"
SRC_ROOT="$HOME/pa"
TC_DIR="$KP_ROOT/prebuilts-master/clang/host/linux-x86/clang-r416183b"
PREBUILTS_DIR="$KP_ROOT/prebuilts/kernel-build-tools/linux-x86"

DO_CLEAN=false
NO_LTO=false
ONLY_CONFIG=false
TARGET=sm8450
DTB_WILDCARD="*"
DTBO_WILDCARD="*"

while [ "${#}" -gt 0 ]; do
    case "${1}" in
        -c | --clean )
                DO_CLEAN=true
                ;;
        -n | --no-lto )
                NO_LTO=true
                ;;
        -o | --only-config )
                ONLY_CONFIG=true
                ;;
        * )
                TARGET="${1}"
                ;;
    esac
    shift
done

if [ -z "$TARGET" ]; then
    echo "Target (device) not specified!"
    exit 1
fi

if ! source .build.rc || [ -z "$SRC_ROOT" ]; then
    echo -e "Create a .build.rc file here and define\nSRC_ROOT=<path/to/aospa/source>"
    exit 1
fi

KERNEL_DIR="$SRC_ROOT/pronoy/android_kernel_xiaomi_sm8450"

if [ ! -d "$KERNEL_DIR" ]; then
    echo "$KERNEL_DIR does not exist!"
    exit 1
fi

KERNEL_COPY_TO="$KERNEL_DIR"
DTB_COPY_TO="$KERNEL_DIR/dtbs"
DTBO_COPY_TO="$DTB_COPY_TO/dtbo.img"
VBOOT_DIR="$KERNEL_DIR/vendor_ramdisk"
VDLKM_DIR="$KERNEL_DIR/vendor_dlkm"

# AK3_DIR="$HOME/AnyKernel3"
# ZIPNAME="aospa-kernel-$TARGET-$(date '+%Y%m%d-%H%M').zip"
# if test -z "$(git rev-parse --show-cdup 2>/dev/null)" &&
#    head=$(git rev-parse --verify HEAD 2>/dev/null); then
#     ZIPNAME="${ZIPNAME::-4}-$(echo $head | cut -c1-8).zip"
# fi

DEFCONFIG="gki_defconfig"
DEFCONFIGS="vendor/waipio_GKI.config \
vendor/xiaomi_GKI.config \
vendor/addon.config \
vendor/debugfs.config"


case "$TARGET" in
    "marble" )
        DTB_WILDCARD="ukee"
        DTBO_WILDCARD="marble-sm7475-pm8008-overlay"
        ;;
    "cupid" )
        DTB_WILDCARD="waipio"
        DTBO_WILDCARD="cupid-sm8450-pm8008-overlay"
        ;;
esac

export PATH="$TC_DIR/bin:$PREBUILTS_DIR/bin:$PATH"

# Fungsi 'make' yang dimodifikasi untuk mencatat error ke log.txt
function m() {
    # Stderr (aliran error) dialihkan ke 'tee' yang akan menampilkannya di konsol
    # dan sekaligus menyimpannya ke dalam file log.
    # Jika 'make' gagal, skrip akan langsung berhenti.
    make -j$(nproc --all) O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 \
        DTC_EXT="$PREBUILTS_DIR/bin/dtc" \
        DTC_OVERLAY_TEST_EXT="$PREBUILTS_DIR/bin/ufdt_apply_overlay" \
        TARGET_PRODUCT=$TARGET $@ 2> >(tee -a "$LOG_FILE") || exit $?
}

$DO_CLEAN && (
    rm -rf out sm8450-modules
    echo "Cleaned output directories."
)

echo -e "Generating config...\n"
mkdir -p out
m $DEFCONFIG
m ./scripts/kconfig/merge_config.sh $DEFCONFIGS vendor/${TARGET}_GKI.config
scripts/config --file out/.config \
    --set-str LOCALVERSION "-NETKERNEL-TEST-1"
$NO_LTO && (
    scripts/config --file out/.config \
        -d LTO_CLANG_FULL -e LTO_NONE \
        --set-str LOCALVERSION "-NETKERNEL-TEST-1"
    echo -e "\nDisabled LTO!"
)

$ONLY_CONFIG && exit

echo -e "\nBuilding kernel...\n"
m Image modules
rm -rf out/modules
m INSTALL_MOD_PATH=modules INSTALL_MOD_STRIP=1 modules_install

echo -e "\nBuilding techpack modules..."
for module in $MODULES; do
    echo -e "\nBuilding $module..."
    m -C $MODULES_SRC/$module M=$MODULES_SRC/$module KERNEL_SRC="$(pwd)" OUT_DIR="$(pwd)/out"
    m -C $MODULES_SRC/$module M=$MODULES_SRC/$module KERNEL_SRC="$(pwd)" OUT_DIR="$(pwd)/out" \
        INSTALL_MOD_PATH=modules INSTALL_MOD_STRIP=1 modules_install
done

echo -e "\nKernel compiled succesfully!\nMerging dtb's...\n"

rm -rf out/dtbs{,-base}
mkdir out/dtbs{,-base}
mv  out/arch/arm64/boot/dts/vendor/qcom/$DTB_WILDCARD.dtb \
    out/arch/arm64/boot/dts/vendor/qcom/$DTBO_WILDCARD.dtbo \
    out/dtbs-base
rm -f out/arch/arm64/boot/dts/vendor/qcom/*.dtbo
# Mencatat error dari skrip python jika ada
../../build/android/merge_dtbs.py out/dtbs-base out/arch/arm64/boot/dts/vendor/qcom/ out/dtbs 2> >(tee -a "$LOG_FILE") || exit $?

echo -e "\nCopying files...\n"

# rm -rf AnyKernel3
# if [ -d "$AK3_DIR" ]; then
#   cp -r $AK3_DIR AnyKernel3
#   git -C AnyKernel3 checkout marble &> /dev/null
# elif ! git clone -q https://github.com/ghostrider-reborn/AnyKernel3 -b marble; then
#   echo -e "\nAnyKernel3 repo not found locally and couldn't clone from GitHub! Aborting..."
#   exit 1
# fi
# KERNEL_COPY_TO="AnyKernel3"
# DTB_COPY_TO="AnyKernel3/dtb"
# DTBO_COPY_TO="AnyKernel3/dtbo.img"
# VBOOT_DIR="AnyKernel3/vendor_boot_modules"
# VDLKM_DIR="AnyKernel3/vendor_dlkm_modules"

cp out/arch/arm64/boot/Image $KERNEL_COPY_TO
echo "Copied kernel to $KERNEL_COPY_TO."

if [ -d "$DTB_COPY_TO" ]; then
    rm -f $DTB_COPY_TO/*.dtb
    cp out/dtbs/*.dtb $DTB_COPY_TO
else
    rm -f $DTB_COPY_TO
    cat out/dtbs/*.dtb >> $DTB_COPY_TO
fi
echo "Copied dtbs to $DTB_COPY_TO"


# Mencatat error dari skrip python jika ada
mkdtboimg.py create $DTBO_COPY_TO --page_size=4096 out/dtbs/*.dtbo 2> >(tee -a "$LOG_FILE") || exit $?
echo "Generated dtbo.img to $DTBO_COPY_TO".

first_stage_modules="$(cat modules.list.msm.waipio)"
second_stage_modules="$(cat modules.list.second_stage modules.list.second_stage.$TARGET)"
vendor_dlkm_modules="$(cat modules.list.vendor_dlkm modules.list.vendor_dlkm.$TARGET)"
modules_out="out/modules/lib/modules/$(ls -t out/modules/lib/modules/ | head -n1)"

rm -rf $VBOOT_DIR && mkdir -p $VBOOT_DIR
rm -rf $VDLKM_DIR && mkdir -p $VDLKM_DIR

echo -e "\nCopying first stage modules..."
for module in $first_stage_modules; do
    mod_path=$(find $modules_out -name "$module" -print -quit)
    if [ -z "$mod_path" ]; then
        echo "Could not locate $module, skipping!"
        continue
    fi
    cp $mod_path $VBOOT_DIR
    echo $module >> $VBOOT_DIR/modules.load
    echo $module >> $VBOOT_DIR/modules.load.recovery
done

echo -e "\nCopying second stage modules..."
for module in $second_stage_modules; do
    mod_path=$(find $modules_out -name "$module" -print -quit)
    if [ -z "$mod_path" ]; then
        echo "Could not locate $module, skipping!"
        continue
    fi
    cp $mod_path $VBOOT_DIR
    cp $mod_path $VDLKM_DIR
    echo $module >> $VBOOT_DIR/modules.load.recovery
    echo $module >> $VDLKM_DIR/modules.load
done

echo -e "\nCopying vendor_dlkm modules..."
for module in $vendor_dlkm_modules; do
    mod_path=$(find $modules_out -name "$module" -print -quit)
    if [ -z "$mod_path" ]; then
        echo "Could not locate $module, skipping!"
        continue
    fi
    cp $mod_path $VDLKM_DIR
    echo $module >> $VDLKM_DIR/modules.load
done

for dest_dir in $VBOOT_DIR $VDLKM_DIR; do
    cp modules.vendor_blocklist.msm.waipio $dest_dir/modules.blocklist
    cp $modules_out/modules.{alias,dep,softdep} $dest_dir
done

sed -E -i 's|([^: ]*/)([^/]*\.ko)([:]?)([ ]\|$)|/lib/modules/\2\3\4|g' $VBOOT_DIR/modules.dep
sed -E -i 's|([^: ]*/)([^/]*\.ko)([:]?)([ ]\|$)|/vendor_dlkm/lib/modules/\2\3\4|g' $VDLKM_DIR/modules.dep

# cd AnyKernel3
# zip -r9 "../$ZIPNAME" * -x .git README.md *placeholder
# cd ..
# rm -rf AnyKernel3

minutes=$((SECONDS / 60))
seconds=$((SECONDS % 60))
echo
echo "Completed in ${minutes} minute(s) and ${seconds} second(s)!"

# echo "$(realpath $ZIPNAME)"
