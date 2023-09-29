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



# build_folder=./build
# project=./make-proj
# 
# 
# check_if_empty(){
#   [ "$(ls -A $build_folder)" ] && return 1 || return 2
# }
# 
# check_if_empty
# 
# check_folder_empty=$?
# 
# if [ "$check_folder_empty" -eq "1" ]; then
#   echo "Building and running in $build_folder"
#   cd $build_folder; make; $project $1 ;
#   printf '\n'
#   echo "Finished"
# elif [ "$check_folder_empty" -eq "2" ]; then
#   echo "Running cmake"
#   cd $build_folder; cmake..;
#   echo "Call $0 again"
# else
#   echo "Nothing to do"
# fi

