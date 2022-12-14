#!/bin/sh

for f in $(cat src/env_list)
do
    bn=$(basename $f)
    
    if ! test -f $bn ; then
        wget $f -O $bn -q
    fi

done;

mkdir ~/tmp/
mv *.xz ~/tmp/
cd ~/tmp/
tar -xf binutils-2.36.1.tar.xz
mv binutils-2.36.1 binutils
tar -xf gcc-10.2.0.tar.xz
mv gcc-10.2.0 gcc
tar -xf glibc-2.33.tar.xz
mv glibc-2.33.tar.xz glibc
tar -xf linux-5.10.17.tar.xz
mv linux-5.10.17 linux
export PREFIX=/opt/armhf

export PATH=$PREFIX/bin:$PATH

# Build binutils
cd ~/tmp/binutils
./configure --prefix=$PREFIX --target=arm-linux-gnueabihf --with-arch=armv7a --with-fpu=vfp --with-float=hard --disable-multilib
make -j4 
make install

cd ~/tmp/linux
make ARCH=arm INSTALL_HDR_PATH=$PREFIX/arm-linux-gnueabihf headers_install

cd ~/tmp/gcc
./contrib/download_prerequisites
mkdir build; cd build
../configure --prefix=$PREFIX --target=arm-linux-gnueabihf --enable-languages=c,c++ --with-arch=armv7-a --with-fpu=vfp --with-float=hard --disable-multilib
make -j4 all-gcc
make install-gcc

cd ~/tmp/glibc
mkdir build; cd build
../configure --prefix=$PREFIX/arm-linux-gnueabihf --build=$MACHTYPE --host=arm-linux-gnueabihf --target=arm-linux-gnueabihf --with-arch=armv7a --with-fpu=vfp --with-float=hard --with-headers=$PREFIX/arm-linux-gnueabihf/include --disable-multilib libc_cv_forced_unwind=yes
make install-bootstrap-headers=yes install-headers
make -j4 csu/subdir_lib
install csu/crt1.o csu/crti.o csu/crtn.o $PREFIX/arm-linux-gnueabihf/lib
arm-linux-gnueabihf-gcc -nostdlib -nostartfiles -shared -x c /dev/null -o $PREFIX/arm-linux-gnueabihf/lib/libc.so
touch $PREFIX/arm-linux-gnueabihf/include/gnu/stubs.h

# Build gcc (second phase, libgcc)
cd ~/tmp/gcc/build
make -j4 all-target-libgcc
make install-target-libgcc

# Build glibc (second phase)
cd ~/tmp/glibc/build
make -j4
make install

# Build libstdc++
cd ~/tmp/gcc/build
make -j4
make install
