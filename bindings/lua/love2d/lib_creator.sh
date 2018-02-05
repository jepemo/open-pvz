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

level_step = ffi.C.level_step
level_add_plant = ffi.C.level_add_plant
level_add_zombie = ffi.C.level_add_zombie
level_destroy = ffi.C.level_destroy

EOF

cat bindings/lua/opvz.lua >> $OUT_FILE

sed -i '/require("libopvz_lua")/d' $OUT_FILE




