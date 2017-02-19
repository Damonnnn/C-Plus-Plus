#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/switch_to.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/poll.h>

#define GLOBALFIFO_SIZE (30) /* the memory size:4K */
#define MEM_CLEAR (0x1) /* clear the memory space */
#define GLOBALFIFO_MAJOR (0) /* predefine major device number */
//#define GLOBALMEM_MAGIC ...
//#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)

static int globalfifo_major = GLOBALFIFO_MAJOR;

struct globalfifo_dev
{
	struct cdev cdev;
	unsigned char mem[GLOBALFIFO_SIZE]; /* the global memory space. */
	unsigned int current_len;
	struct semaphore sem; /*并发控制用的信号量*/
	wait_queue_head_t r_wait; /*阻塞读用的等待队列头*/
	wait_queue_head_t w_wait; /*阻塞写用的等待队列头*/
	struct fasync_struct *async_queue; //异步通知相关的结构
};



