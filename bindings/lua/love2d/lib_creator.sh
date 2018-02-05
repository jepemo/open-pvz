#!/bin/bash

OUT_FILE=./bindings/lua/love2d/opvz.lua
SRC_DIR=./src


echo "local ffi = require \"ffi\"" > $OUT_FILE
echo -ne "ffi.cdef[[\n" >> $OUT_FILE

# Headers
cat $SRC_DIR/*.h >> $OUT_FILE
echo "" >> $OUT_FILE
# Code
cat $SRC_DIR/*.c >> $OUT_FILE
echo "" >> $OUT_FILE

echo -ne "]]\n" >> $OUT_FILE

cat >> $OUT_FILE <<- EOF

local libopvz = ffi.load("libopvz.so")

local level_step = libopvz.level_step
local level_add_plant = libopvz.level_add_plant
local level_add_zombie = libopvz.level_add_zombie
local level_destroy = libopvz.level_destroy

EOF

cat bindings/lua/opvz.lua >> $OUT_FILE

sed -i '/require("libopvz_lua")/d' $OUT_FILE
sed 's|/\*|\n&|g;s|*/|&\n|g' $OUT_FILE | sed '/\/\*/,/*\//d' > ${OUT_FILE}_2
mv ${OUT_FILE}_2 $OUT_FILE

sed -i '/^#include.*/d' $OUT_FILE
sed -i '/#ifndef __OPVZ_.*/d' $OUT_FILE
sed -i '/#define __OPVZ_.*/d' $OUT_FILE
sed -i '/#endif.*/d' $OUT_FILE
sed -i '/^\s*$/d' $OUT_FILE




