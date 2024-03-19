#!/bin/sh

set -xe

cd /tmp
cmake -DCMAKE_INSTALL_PREFIX=~/.local \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_UNITY_BUILD=ON -DCMAKE_UNITY_BUILD_BATCH_SIZE=32 \
      -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic -Werror -D_GLIBCXX_ASSERTIONS -fno-inline --coverage" \
      -DSWIG_COMPILE_FLAGS="-O1 -Wno-unused-parameter" \
      -DSPHINX_FLAGS="-W -T -j4" \
      -B build /io
cd build
make install
make tests
ctest --output-on-failure --timeout 100 ${MAKEFLAGS}
lcov --no-external --capture --initial --directory $PWD --output-file lcov.info

uid=$1
gid=$2
if test -n "${uid}" -a -n "${gid}"
then
  sudo cp -r ~/.local/share/doc/*/html lcov.info /io
  sudo chown -R ${uid}:${gid} /io/html /io/lcov.info
fi
