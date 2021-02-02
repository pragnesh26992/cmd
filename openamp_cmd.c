========== hugetlbfs ===============

git clone git@github.com:libhugetlbfs/libhugetlbfs.git

export LD=riscv64-unknown-linux-gnu-ld
export CC=riscv64-unknown-linux-gnu-gcc
export ARCH=riscv64
make VERBOSE=1

========== sysfsutils linux ===================

git clone https://github.com/Distrotech/sysfsutils
cd sysfsutils
autoreconf -f -i
./configure --build=`./config.guess` CFLAGS=-fPIC --host=riscv64-unknown-linux-gnu
make
cd include
mkdir sysfs
cp libsysfs.h dlist.h sysfs/


========== libmetal baremetal ================

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk.cmake
make VERBOSE=1 DESTDIR=./install/ install


========== libmetal linux =====================

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk-linux.cmake -DLIBSYSFS_LIBRARY=/india/proj_ssw/work/pragneshp/opensource/sysfsutils/lib/.libs/libsysfs.a -DLIBRT_LIBRARIES=/data/x-tools/riscv64-unknown-linux-gnu/riscv64-unknown-linux-gnu/sysroot/usr/lib64/lp64d/librt.so  -DWITH_DOC=OFF -DCMAKE_INCLUDE_PATH=/india/proj_ssw/work/pragneshp/opensource/sysfsutils/include -DHUGETLBFS_LIBRARY=/india/proj_ssw/work/pragneshp/opensource/libhugetlbfs/obj64/libhugetlbfs.so -DWITH_TESTS=OFF

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk-linux.cmake -DLIBSYSFS_LIBRARY=/home/pragneshp/opensource/sysfsutils/lib/.libs/libsysfs.a -DLIBRT_LIBRARIES=/home/pragneshp/x-tools/riscv64-unknown-linux-gnu/riscv64-unknown-linux-gnu/sysroot/usr/lib64/lp64d/librt.so -DWITH_TESTS=OFF -DWITH_DOC=OFF -DCMAKE_INCLUDE_PATH=/home/pragneshp/opensource/sysfsutils/include/

make VERBOSE=1 DESTDIR=./install/ install

========= libopen-amp baremetal ===============

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk.cmake -DCMAKE_INCLUDE_PATH=/home/pragneshp/opensource/libmetal/build-baremetal/install/usr/local/include -DCMAKE_LIBRARY_PATH=/home/pragneshp/opensource/libmetal/build-baremetal/install/usr/local/lib 

make VERBOSE=1 DESTDIR=./install/ install

========= libopen-amp linux ===================

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk-linux.cmake -DLIBMETAL_INCLUDE_DIR=/india/proj_ssw/work/pragneshp/opensource/libmetal/sifive-u-build-linux/install/usr/local/include -DCMAKE_LIBRARY_PATH=/india/proj_ssw/work/pragneshp/opensource/libmetal/sifive-u-build-linux/install/usr/local/lib -DWITH_APPS=ON

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/e-sdk-linux.cmake -DCMAKE_INCLUDE_PATH=/home/pragneshp/opensource/libmetal/build-linux/install/usr/local/include -DCMAKE_LIBRARY_PATH=/home/pragneshp/opensource/libmetal/build-linux/install/usr/local/lib -DWITH_APPS=ON

make VERBOSE=1 DESTDIR=./install/ install


================== CPIO Unpack and Pack =================
To unpack:

gunzip initramfs.cpio.gz
mkdir src && cd ./src
sudo cpio -id < ../initramfs.cpio


To pack:

// Change permision of etc/shadow to 644
sudo find . | cpio --create --format='newc' > /tmp/newinitrd.cpio
gzip /tmp/newinitrd.cpio

