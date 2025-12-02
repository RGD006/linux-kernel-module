// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/klist.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Vladyslav Sukhomlin <sukhomlin.vladyslav@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training.\nWrite time of each 'hello world' output");
MODULE_LICENSE("Dual BSD/GPL");

struct kernel_time {
	struct list_head list;
	unsigned int number; // output number
	ktime_t time; // output time
};

static LIST_HEAD(output_list);

unsigned int hello_count = 1;

static int __init hello_init(void)
{
	if (hello_count > 10) {
		pr_err("Can't start. Too big parameter hello-count\n");
		return -EINVAL;
	} else if (hello_count >= 5 && hello_count <= 10) {
		pr_warn("Too big parameter hello-count\n");
	} else if (hello_count == 0) {
		pr_warn("hello-count parameter equal 0. Nothing to output");
	}

	for (unsigned int i = 0; i < hello_count; i++) {
		struct kernel_time *o_time = kmalloc(sizeof(struct kernel_time), GFP_KERNEL);

		o_time->time = ktime_get();
		o_time->number = i;
		list_add(&o_time->list, &output_list);

		pr_emerg("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct list_head *pos, *n;

	pr_emerg("Exit module. Write some data info\n");

	list_for_each_safe(pos, n, &output_list) {
		struct kernel_time *data = container_of(pos, struct kernel_time, list);

		pr_emerg("number: %u | time: %llu\n", data->number, data->time);

		kfree(data);
		list_del(pos);
	}
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_PARM_DESC(hello_count, "The number of 'Hello, world!' output");
module_param(hello_count, uint, 0444);
