#include "linux/kernel.h"
#include "linux/module.h"
#include "linux/fs.h"
#include "linux/init.h"
#include "linux/types.h"
#include "linux/errno.h"
#include "linux/uaccess.h"
#include "linux/kdev_t.h"
#include <uapi/linux/in.h>
#include "linux/kthread.h"
#include "linux/delay.h"
#include "linux/semaphore.h"
#include "linux/workqueue.h"
#include "linux/timer.h"
#include "linux/sched.h"
#include "linux/jiffies.h"
#define MAX_SIZE 1024
int my_open(struct inode *inode, struct file *file);
int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f);
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f);
 
char message[MAX_SIZE] = "this is a origin message";
int device_num;//设备号
char* devName = "damonDriver";//设备名

DEFINE_SEMAPHORE(dbg_semaphore);
struct work_struct tx_work;
struct workqueue_struct *tx_queue;
struct timer_list dbg_timer;
struct task_struct *dbg_task;
unsigned int dbg_index = 0;
struct file_operations pStruct =
{ 
	open:my_open, 
	release:my_release, 
	read:my_read, 
	write:my_write, 
};

unsigned short t1 = 0;
struct s1 {
	int __attribute__((bitwise)) f;

};

void my_delay(unsigned int msec)
{
	//unsigned long timeout = jiffies + msecs_to_jiffies(msec);
	//while(time_after(jiffies, timeout)) {
	//	break;
	//}
	volatile unsigned int loopa = 0, loopb = 0, sum = 0;
	for(loopa = msec; loopa >= 0; loopa--) {
		for(loopb = 100; loopb >= 0; loopa--) {
			sum++;
		}	
	} 
}

int dbg_thread(void *data)
{
	struct sched_param param;
	int loop = 20, i;
	param.sched_priority = 0;//the highest
	sched_setscheduler(current, SCHED_FIFO, &param);
	printk("%10u-dbg:this is dbg_thread \n", dbg_index++);
	while(1) {
//		down(&dbg_semaphore);
		//printk("%10u-dbg: before looping\n",dbg_index++);
		//mdelay(20);
		for(i = 0; i < loop; i++) {
			if(i == 0){
				printk("%10u-dbg:dbg_thread looping...\n", dbg_index++);
			} else if (i == (loop - 1)) {
				printk("%10u-dbg:dbg_thread looping end\n", dbg_index++);
			}
		}
		//printk("%10u-dbg: after looping\n",dbg_index++);
		printk("%10u-dbg: before sleep\n",dbg_index++);
		msleep(10);
		printk("%10u-dbg: after sleep\n",dbg_index++);
		//queue_work(tx_queue, &tx_work);
	//	printk("%10u-dbg:queue work called\n",dbg_index++);

		if (kthread_should_stop()) {
			printk("%10u-dbg: dbg_thread byebye...\n",dbg_index++);
			return 0;
		}

	}
}

void tx_work_queue(struct work_struct *work)
{
	int loop = 500000000, i;
	printk("%10u-dbg:this is tx_work_queue\n", dbg_index++);
	//mdelay(50);//busy wait
	for(i = 0; i < loop; i++) {
		if(i == 0){
			printk("%10u-dbg:tx_work_queue looping...\n", dbg_index++);
		} else if (i == (loop - 1)) {
			printk("%10u-dbg:tx_work_queue looping end-%d\n", dbg_index++, i);
		}
	}
	printk("%10u-dbg:tx_work_queue over\n", dbg_index++);
//	up(&dbg_semaphore);
}


void test_timer_fn(unsigned long arg)
{
	static int flag = 0;
	printk("%10u-dbg:this is test timer\n",dbg_index++);
	queue_work(tx_queue, &tx_work);
	if (flag == 0) {
		wake_up_process(dbg_task);
		flag = 1;
	}
	mod_timer(&dbg_timer, jiffies + msecs_to_jiffies(10000));//timeout after 1000ms
	printk("%10u-dbg:test timer over\n",dbg_index++);
}

/* init module */
int init_module()
{
	int ret;
	sema_init(&dbg_semaphore, 2);
	dbg_task = kthread_create(dbg_thread, NULL, "dbg_thread");
	if (dbg_task) {
		//wake_up_process(dbg_task);
	} else {
		printk("%10u-dbg:create dbg_thread failed \n", dbg_index++);	
	}
	
	tx_queue = alloc_ordered_workqueue("SPRDWL_TX_QUEUE",
							            WQ_MEM_RECLAIM |
							 		    WQ_HIGHPRI | 
										WQ_CPU_INTENSIVE);
	INIT_WORK(&tx_work, tx_work_queue);
	//queue_work(tx_queue, &tx_work);

	init_timer(&dbg_timer);
    dbg_timer.function= test_timer_fn;
    add_timer(&dbg_timer);
	mod_timer(&dbg_timer, jiffies + msecs_to_jiffies(1000));//timeout after 1000ms

	ret = register_chrdev(0, devName, &pStruct);
	if (ret < 0)
	{
		printk("%10u-dbg:failed to register_chrdev.\n", dbg_index++);
		return -1;
	}
	else
	{
		printk("%10u-dbg:the damonDriver has been registered!\n", dbg_index++);
		printk("id: %d\n", ret);
		device_num = ret;
 
		return 0;
	}
}
 
/* exit module */
void cleanup_module()
{
	del_timer(&dbg_timer);
	kthread_stop(dbg_task); //kthread_should_stop() will become true
	destroy_workqueue(tx_queue);
	unregister_chrdev(device_num, devName);
	printk("unregister successful.\n");
}
 
 
/* open function */
int my_open(struct inode *inode, struct file *file)
{
	printk("open damonDriver OK!\n");
	try_module_get(THIS_MODULE);
	return 0;
}
 
/* release function */
int my_release(struct inode *inode, struct file *file)
{
	printk("Device released!\n");
	module_put(THIS_MODULE);
 
	return 0;
}
 
 
/* read function */
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
	if(copy_to_user(user,message,sizeof(message)))
	{
		return -2;
	}
	return sizeof(message);
}
 
/* write function */
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
	int i = 0;
	while(i++ < 5) {
		printk("[damon] %d warn_on", i);
		WARN_ON(1);
	}
	if(copy_from_user(message,user,sizeof(message)))
	{
		return -3;
	}
	return sizeof(message);
}

MODULE_LICENSE("GPL");

