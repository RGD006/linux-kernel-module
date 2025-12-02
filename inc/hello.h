#ifndef __HELLO_H__
#define __HELLO_H__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/klist.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct kernel_time {
	struct list_head list;
	unsigned int number; // output number
	ktime_t time; // output time
};

int print_hello(unsigned int hello_count);

extern unsigned int hello_count;

#endif
