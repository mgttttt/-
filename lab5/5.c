#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/mutex.h>

#define DEVICE_NAME "pid_data"
#define CLASS_NAME "pid_data_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail");
MODULE_DESCRIPTION("A simple Linux character device driver for inter-process communication storing and retrieving data by PID.");
MODULE_VERSION("1");

static int major_number;
static struct class *device_class;
static struct device *device_data;

static DEFINE_MUTEX(pid_data_mutex);

struct pid_data_entry {
    pid_t pid;
    char data[256];
    struct list_head list;
};

static LIST_HEAD(pid_data_list);

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static int dev_open(struct inode *inodep, struct file *filep);
static int dev_release(struct inode *inodep, struct file *filep);

static struct file_operations fops = {
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release,
};

static int __init pid_data_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number for %s\n", DEVICE_NAME);
        return major_number;
    }

    device_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(device_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class for %s\n", DEVICE_NAME);
        return PTR_ERR(device_class);
    }

    device_data = device_create(device_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(device_data)) {
        class_destroy(device_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device for %s\n", DEVICE_NAME);
        return PTR_ERR(device_data);
    }

    mutex_init(&pid_data_mutex);
    printk(KERN_INFO "%s: device class created successfully\n", DEVICE_NAME);
    return 0;
}

static void __exit pid_data_exit(void) {
    device_destroy(device_class, MKDEV(major_number, 0));
    class_unregister(device_class);
    class_destroy(device_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    mutex_destroy(&pid_data_mutex);

    struct pid_data_entry *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &pid_data_list, list) {
        list_del(&entry->list);
        kfree(entry);
    }

    printk(KERN_INFO "%s: device class removed successfully\n", DEVICE_NAME);
}

static int dev_open(struct inode *inodep, struct file *filep) {
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    pid_t pid;
    struct pid_data_entry *entry;
    int found = 0;
    ssize_t data_len;

    if (len < sizeof(pid_t)) {
        return -EINVAL;
    }

    if (copy_from_user(&pid, buffer, sizeof(pid_t))) {
        return -EFAULT;
    }

    mutex_lock(&pid_data_mutex);
    list_for_each_entry(entry, &pid_data_list, list) {
        if (entry->pid == pid) {
            found = 1;
            break;
        }
    }

    if (!found)    {
        mutex_unlock(&pid_data_mutex);
        return -ENOENT;
    }

    data_len = strlen(entry->data);
    if (len < data_len + sizeof(pid_t)) {
        mutex_unlock(&pid_data_mutex);
        return -EOVERFLOW;
    }

    if (copy_to_user(buffer + sizeof(pid_t), entry->data, data_len)) {
        mutex_unlock(&pid_data_mutex);
        return -EFAULT;
    }

    mutex_unlock(&pid_data_mutex);
    return sizeof(pid_t) + data_len;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    pid_t pid;
    struct pid_data_entry *entry;
    int found = 0;

    if (len < sizeof(pid_t) || len > sizeof(pid_t) + sizeof(entry->data)) {
        return -EINVAL;
    }

    if (copy_from_user(&pid, buffer, sizeof(pid_t))) {
        return -EFAULT;
    }

    mutex_lock(&pid_data_mutex);
    list_for_each_entry(entry, &pid_data_list, list) {
        if (entry->pid == pid) {
            found = 1;
            break;
        }
    }

    if (!found) {
        entry = kmalloc(sizeof(struct pid_data_entry), GFP_KERNEL);
        if (!entry) {
            mutex_unlock(&pid_data_mutex);
            return -ENOMEM;
        }
        entry->pid = pid;
        list_add(&entry->list, &pid_data_list);
    }

    if (copy_from_user(entry->data, buffer + sizeof(pid_t), len - sizeof(pid_t))) {
        mutex_unlock(&pid_data_mutex);
        return -EFAULT;
    }
    entry->data[len - sizeof(pid_t)] = '\0';

    mutex_unlock(&pid_data_mutex);
    return len;
}

module_init(pid_data_init);
module_exit(pid_data_exit);