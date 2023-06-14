#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/poll.h>
#include <linux/mutex.h>

#define DEVICE_NAME "sort"

static dev_t dev_num;
static struct cdev c_dev;
static struct class *cl;

static int open(struct inode *inode, struct file *file) 
{
    return 0;
}

static ssize_t read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    char *temp_buf = kmalloc(1024, GFP_KERNEL);
    size_t length = 0;
    size_t temp_len = 0;
    size_t temp = len;
    char sorted[1024];
    if (copy_from_user(temp_buf, buf, len)) {
        return -EFAULT;
    }

    while (temp)
    {
        temp--;
        sorted[temp] = temp_buf[temp];
    }

    while(length != len) {
        temp_len = length + 1;
        while ((temp_len != len - 1) && (temp_len != len))
        {
            if (sorted[temp_len] < sorted[length])
            {
                char t = sorted[temp_len];
                sorted[temp_len] = sorted[length];
                sorted[length] = t;
            }
            temp_len++;
        }
        length++;
    }
    sorted[len] = '\0';
    if (copy_to_user(buf, sorted, len))
        return -EFAULT;
    return len; 
}

static struct file_operations fops = {
    .owner   =  THIS_MODULE,
    .open    =  open,
    .read    =  read,
};

static int __init sort_init(void) 
{
    int ret;
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret) {
        pr_err("Failed to allocate char device region\n");
        return ret;
    } 

    cdev_init(&c_dev, &fops);
    c_dev.owner = THIS_MODULE;
    ret = cdev_add(&c_dev, dev_num, 1);
    if (ret) {
        pr_err("Failed to add cdev\n");
        goto unregister;
    }

    cl = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cl, NULL, dev_num, NULL, DEVICE_NAME);

    pr_info("sorter loaded\n");
    return 0;

unregister:
    unregister_chrdev_region(dev_num, 1);
    return ret;
}

static void __exit sort_exit(void) 
{
    device_destroy(cl, dev_num);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev_num, 1); 
    pr_info("sorter unloaded\n");
}

module_init(sort_init);
module_exit(sort_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("maks"); 
MODULE_DESCRIPTION("sorting digits and letters");