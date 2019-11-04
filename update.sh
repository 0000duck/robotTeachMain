#!/bin/bash

basepath=$(cd `dirname $0`; pwd)

cd $basepath
cd ../../
mkdir ./TEMP

filepath=$(find /media -name "update_HR_ROBOT.tar.xz")

echo $filepath

cp $filepath ./TEMP/

tar xvf ./TEMP/update_HR_ROBOT.tar.xz -C ./TEMP
source ./TEMP/update_HR_ROBOT/setting.sh

rm -rf ./TEMP



