#!/bin/bash

cargo bootimage
qemu-system-x86_64 -drive format=raw,file=target/cognitOS/debug/bootimage-cognitOS.bin
