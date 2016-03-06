#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>

MODULE_AUTHOR("Ma James");
MODULE_LICENSE("GPL");
static char *whom = "world";
static int howmany = 1;
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

int mymod_read_procmem(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
    int len=0;
    len = sprintf(buf, "this is a test from mymod howmany: %d, whom: %s, max len: %d\n", howmany, whom, count);
    *eof = 1;
    return len;
}

static int __init mine_init(void)
{
	int i;
	for(i=0;i<howmany;i++)
		printk(KERN_ALERT "Hello, How are you. %s\n", whom);
//    proc_create_data("mymod", 0, NULL, mymod_read_procmem, NULL);
	return 0;
}

static void __exit mine_exit(void)
{
	printk(KERN_ALERT "I am going to leave, Unloaded\n");
 //   remove_proc_entry("mymod", NULL);
}
EXPORT_SYMBOL(whom);
module_init(mine_init);
module_exit(mine_exit);

