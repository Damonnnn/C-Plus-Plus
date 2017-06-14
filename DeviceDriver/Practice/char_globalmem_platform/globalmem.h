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

#define GLOBALMEM_SIZE (0x1000) /* the memory size:4K */
#define MEM_CLEAR (0x1) /* clear the memory space */
#define GLOBALMEM_MAJOR (0) /* predefine major device number */
//#define GLOBALMEM_MAGIC ...
//#define MEM_CLEAR _IO(GLOBALMEM_MAGIC, 0)

static int globalmem_major = GLOBALMEM_MAJOR;

struct globalmem_dev
{
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE]; /* the global memory space. */
};

struct globalmem_dev dev;
