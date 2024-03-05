#include<linux/kernel.h>
#include<linux/sched/signal.h>
#include<linux/moduleparam.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs_struct.h>



MODULE_LICENSE("Kunal");
MODULE_AUTHOR("Sharma");

//MODULE_PARM_DESC(mystring,"Taking command line argument mystring");

static char *mystring = "anything";
module_param(mystring,charp,0);



static int My_Module_init(void)
{
    struct task_struct *task_list;
    for_each_process(task_list)
    {

        if ((strcmp(task_list->comm, mystring)) == 0)
        {
            
            printk(KERN_ALERT "The pid of the process is: %d\n", task_list->pid);
            printk(KERN_ALERT "The user_id of the process is: %d\n", task_list->cred->uid);
            printk(KERN_ALERT "The pgid of the process is: %d\n", task_list->group_leader->pid);
            printk(KERN_ALERT "command path: %s\n", task_list->fs->pwd);

        }
    }
    
    return 0;
}

static void My_Module_exit(void)
{
    printk(KERN_ALERT "Module have been unloaded\n");
}

module_init(My_Module_init);i
module_exit(My_Module_exit);
