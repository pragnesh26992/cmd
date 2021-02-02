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

========== libmetal linux =====================

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/sifive-u-linux.cmake -DLIBSYSFS_LIBRARY=/india/proj_ssw/work/pragneshp/opensource/sysfsutils/lib/.libs/libsysfs.a -DLIBRT_LIBRARIES=/data/x-tools/riscv64-unknown-linux-gnu/riscv64-unknown-linux-gnu/sysroot/usr/lib64/lp64d/librt.so  -DWITH_DOC=OFF -DCMAKE_INCLUDE_PATH=/india/proj_ssw/work/pragneshp/opensource/sysfsutils/include -DHUGETLBFS_LIBRARY=/india/proj_ssw/work/pragneshp/opensource/libhugetlbfs/obj64/libhugetlbfs.so -DWITH_TESTS=OFF

make VERBOSE=1 DESTDIR=./install/ install

========= libopen-amp linux ===================

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/sifive_u_linux.cmake -DLIBMETAL_INCLUDE_DIR=/india/proj_ssw/work/pragneshp/opensource/libmetal/sifive-u-build-linux/install/usr/local/include   -DWITH_APPS=ON  -DCMAKE_LIBRARY_PATH=/india/proj_ssw/work/pragneshp/opensource/libmetal/sifive-u-build-linux/install/usr/local/lib

make VERBOSE=1 DESTDIR=./install/ install


