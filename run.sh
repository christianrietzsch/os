#/bin/bash
sh scripts/make.sh
sh scripts/start.sh
rm kernel
rm boot/objects/init.o
rm boot/objects/start.o
