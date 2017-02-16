#include "globalfifo.h"

static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index);
static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos);
static ssize_t globalfifo_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos);
static int globalfifo_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, unsigned long arg);
static int globalfifo_open(struct inode* inode, struct file *filp);
static int globalfifo_release(struct inode* inode, struct file *filp);

struct globalfifo_dev *globalfifo_devp;

static const struct file_operations globalfifo_fops = 
{
	.owner = THIS_MODULE,
	.read = globalfifo_read,
	.write = globalfifo_write,
	.unlocked_ioctl = globalfifo_ioctl,
	.open = globalfifo_open,
	.release = globalfifo_release,
};

static int globalfifo_open(struct inode* inode, struct file *filp)
{
	printk(KERN_INFO "dbg: I am opened...");
	filp->private_data = (void *)globalfifo_devp;
	return 0;
}

static int globalfifo_release(struct inode* inode, struct file *filp)
{
	printk(KERN_INFO "dbg: I am released...");
	return 0;
}

static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index)
{
	int err, devno = MKDEV(globalfifo_major, index);

	cdev_init(&dev->cdev, &globalfifo_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &globalfifo_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		printk(KERN_NOTICE "Error %d adding LED%d", err, index);
	}
}

int globalfifo_init(void)
{
	int ret;
	dev_t devno = MKDEV(globalfifo_major, 0);

	printk(KERN_INFO "dbg: I am init...");
	if (globalfifo_major) {
		ret = register_chrdev_region(devno, 1, "globalfifo");
	} else {
		ret = alloc_chrdev_region(&devno, 0, 1, "globalfifo");
		globalfifo_major = MAJOR(devno);
	}
	if (ret < 0) {
		return ret;
	}
	
	globalfifo_devp = kmalloc(sizeof(struct globalfifo_dev), GFP_KERNEL);
	if (!globalfifo_devp) { 
		ret = - ENOMEM;
		goto fail_malloc;
	}
	memset((void *)globalfifo_devp, 0, sizeof(struct globalfifo_dev));

	globalfifo_setup_cdev(globalfifo_devp, 0);

	sema_init(&globalfifo_devp->sem, 1); 
	init_waitqueue_head(&globalfifo_devp->r_wait); 
	init_waitqueue_head(&globalfifo_devp->w_wait); 

	return 0;

	fail_malloc: unregister_chrdev_region(devno, 1);
	return ret;
}

/* globalmem module unloading function */
void globalfifo_exit(void)
{
	printk(KERN_INFO "dbg: I am exit...");
	cdev_del(&(globalfifo_devp->cdev));
	unregister_chrdev_region(MKDEV(globalfifo_major, 0), 1); /*clear up the device*/
	kfree(globalfifo_devp);
}


static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	int ret;
	struct globalfifo_dev *dev = filp->private_data; 
	DECLARE_WAITQUEUE(wait, current);
	printk(KERN_INFO "dbg: I am read,count=%d...",count);
	down(&dev->sem); 
	add_wait_queue(&dev->r_wait, &wait); 

	
	if (dev->current_len == 0) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = - EAGAIN;
			goto out;
		}
		__set_current_state(TASK_INTERRUPTIBLE); 
		up(&dev->sem);
		printk(KERN_INFO "dbg: I sleep here...");
		schedule(); 
		printk(KERN_INFO "dbg: I wakeup here...");
		if (signal_pending(current)) {
		
			ret = - ERESTARTSYS;
			goto out2;
		}

		down(&dev->sem);
	}

	
	if (count > dev->current_len) {
		count = dev->current_len;
	}

	if (copy_to_user(buf, dev->mem, count)) {
		ret = - EFAULT;
		goto out;
	} else {
		memcpy(dev->mem, dev->mem + count, dev->current_len - count); 
		dev->current_len -= count; 
		printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);

		wake_up_interruptible(&dev->w_wait); 

		ret = count;
	}
	out: up(&dev->sem); 
	out2: remove_wait_queue(&dev->w_wait, &wait); 
	set_current_state(TASK_RUNNING);
	return ret;
}



static ssize_t globalfifo_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct globalfifo_dev *dev = filp->private_data; 
	int ret;
	DECLARE_WAITQUEUE(wait, current); 
	printk(KERN_INFO "dbg: I am write...");
	down(&dev->sem); 
	add_wait_queue(&dev->w_wait, &wait); 

	
	if (dev->current_len == GLOBALFIFO_SIZE) {
		if (filp->f_flags &O_NONBLOCK) {
			
			ret = - EAGAIN;
			goto out;
		}
		__set_current_state(TASK_INTERRUPTIBLE); 
		up(&dev->sem);

		schedule(); 
		if (signal_pending(current)) {
			
			ret = - ERESTARTSYS;
			goto out2;
		}

		down(&dev->sem); 
	}

	
	if (count > GLOBALFIFO_SIZE - dev->current_len) {
		count = GLOBALFIFO_SIZE - dev->current_len;
	}

	if (copy_from_user(dev->mem + dev->current_len, buf, count)) {
		ret = - EFAULT;
		goto out;
	} else {
		dev->current_len += count;
		printk(KERN_INFO "written %d bytes(s),current_len:%d\n", count, dev->current_len);
		wake_up_interruptible(&dev->r_wait); 
		ret = count;
	}

	out: up(&dev->sem); 
	out2: remove_wait_queue(&dev->w_wait, &wait); 
	set_current_state(TASK_RUNNING);
	return ret;
}


static int globalfifo_ioctl(struct inode *inodep, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalfifo_dev *dev = filp->private_data; 
	printk(KERN_INFO "dbg: I am ioctl...");
	switch (cmd)
	{
		case MEM_CLEAR:
			if (down_interruptible(&dev->sem)) {
				return - ERESTARTSYS;
			}
			memset(dev->mem, 0, GLOBALFIFO_SIZE);
			up(&dev->sem); 

			printk(KERN_INFO "globalmem is set to zero\n");
			break;

		default:
			return - EINVAL;
	}
	return 0;
}


MODULE_AUTHOR("Damon Li");
MODULE_LICENSE("Dual BSD/GPL");

module_param(globalfifo_major, int, S_IRUGO);

module_init(globalfifo_init);
module_exit(globalfifo_exit);


