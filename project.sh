#!/bin/bash

pwd > read_address
read address < read_address
file_control=control            #truyen file_control bang file control

if [ ! -f $file_control ]  #check file exist
    then
    echo "File \"${file_control}\" khong ton tai"
    echo "Thoat"
    exit 1
fi

# kiemtra & delete dir : pro.image
if [ -d ../pro.image ]
    then
    rm -rf ../pro.image     #remove folder cu
fi
mkdir ../pro.image         #tao thu muc pro.image
mkdir ../pro.image/bin/    #tao thu muc bin trong pro.image

#read noi dung cua file control
while read line
do
    ln -s $address/${line} ../pro.image
    cd ../pro.image/${line}/
    make >/dev/null     #makefile
    if [ -x ${line} ]
        then
        cd .. #tra ve thu muc pro.
        cp ./${line}/${line} ./bin
    fi
done < ${file_control}

echo "SUCCESS"

exit 0