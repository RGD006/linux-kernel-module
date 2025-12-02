#include "hello.h"

MODULE_AUTHOR("Vladyslav Sukhomlin <sukhomlin.vladyslav@lll.kpi.ua>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training.\nn number 'hello world' output");
MODULE_LICENSE("Dual BSD/GPL");

unsigned int hello_count = 1;

static int __init hello_init(void)
{
  pr_info("start hello2 module");
  return print_hello(hello_count);
}

static void __exit hello_exit(void)
{
  pr_info("stop hello2 module");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_PARM_DESC(hello_count, "The number of 'Hello, world!' output");
module_param(hello_count, uint, 0444);
