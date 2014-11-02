#!/usr/bin/env bash
# Run this to build project with cmake
# Alternative to my normal makefiles
ROOT=$(readlink -f $(dirname $0))
BDIR=$ROOT/gen

usage() {
  echo "USAGE: ./$(basename $0) OPT1 OPT2 ...
    clean    : Remove build dir.
    main     : Build main project.

  NB: Be sure to 'clean' before switching between projects.
  i.e. ./build.sh clean python"
}

build() {
  if [ "$(uname -s)" == "Linux" -a ! -d ./libs ]; then
    ./GetLibs.py argtable libxml gtest jansson
  fi

  pushd "$BDIR"
  if [ ! -f "$BDIR/CMakeCache.txt" ]; then
    cmake $@ ..
  fi
  make
  popd
}

if [ -z "$1" ]; then
  usage
  exit
fi

for arg; do
  case "$arg" in
    *help|-h)
      usage
      exit
      ;;
    clean)
      rm -rf "$BDIR"
      mkdir -p "$BDIR"
      touch "$BDIR/DUMMY"
      ;;
    main)
      build
      ;;
    *)
      echo "Invalid command, see the help."
      ;;
  esac
done
