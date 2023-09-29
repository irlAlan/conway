#!/usr/bin/bash

build_dir="build/"
project="conway"

is_empty(){
  [ "$(ls -A $build_dir)" ] && return 1 || return 2
}
is_empty

check_if_empty=$?

if [ "$check_if_empty" -eq "1" ]; then
  printf "Running $project in $build_dir"
  cmake --build $build_dir; cd $build_dir; ./$project
  printf '\n'
  printf "Finished!\n"
elif [ "$check_if_empty" -eq "2" ]; then
  printf "Building and Running the program\n"
  cmake -B $build_dir; cmake --build $build_dir;
  printf "Finished!\n"
  cd $build_dir; ./$project;
else
  printf "There is nothing to do :( \n"
fi
