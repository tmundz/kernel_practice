1. In-source Tree: Modules present in the Linux Kernel Source Code
2. Out-of Tree: Modules not present in the Linux Kernel Source Code.


all modules will start as out-of-tree developments, that can be compiled using the context of a source-tree. once a module gets accepted to be inculded it will become in-source tree

kernel modules nee a start and end point

module_init() and module_exit() macros

modules should specify whicfh license you are using 

header file needed is linux/module.h printk instead of printf

lsmod lists modules loaded

commands for a kernel compilation in C
make -C /lib/modules/6.0.11-arch1-1/build/ M=${PWD} modules
make -C /lib/modules/6.0.11-arch1-1/build/ M=${PWD} clean to clean the files created

load module in the kernel use insmod
ex.
sudo insmod ./hello.ko

remove module use rmmod

sudo rmmod hello


<h3>Cross compilation</h3>
ARCH and CROSS_COMPILE need to be specified 

CROSS_COMPILE usually = x86_64-pc-linux-gnu-gcc to make it cross compile 
