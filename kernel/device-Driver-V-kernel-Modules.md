Kernel modules may nopt be a device driver at all where as a driver is much like a sub-class of a module:
<h3>Kernel Modules</h3>
1. Device drivers,
2. File Systems
3. System Calls
4. Network drivers: Drivers implementing a network protocol (TCP/IP)
5. TTY line disxiplines: For terminal devices

<h3>Advantages of kernel modules</h3>

1. All parts of the base kernel stay loaded all the time. Modules can save you memory, because you have to have them loaded only when you're actually using them
2. Users would need to rebuild and reboot the kernel every time they would require a new functionality.
3. A bug in driver which is compiled as a part of kernel will stop system from loading, whereas modules allows systems to load.
4. Faster to maintain and debug
5.  Makes it easer to maintain multiple machines on a single kernel base.

<h3>Disadvantages of Kernel Modules</h3>
1.  Size: Module  managment consumes unpageable kernel memory. Modules will consume more memory then drivers compiled into the kernel itself
2. as modules are loaded later in the boot process, hence core functionality has to go in the base kernel ex mem managment
3.  Security: If you build your kernel statically and disable linux dynamic module loading feature, you prvent run-time modification of the kernel code

<h3>Configuration</h3>
In order to support modules the kernel must have been built with the follwoing options

CONFIG_MODULES=y




