#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "crypto_chardev"
#define KEY 0xAB

static int major_number;
static struct class *device_class;
static struct device *device_data;
char data[1024];

ssize_t crypto_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    int i;
    //char decrypted_data[1024];
    // if (copy_from_user(data, buf, count)) {
    //     return -EFAULT;
    // }

    for (i = 0; i < count; i++) {
        data[i] ^= KEY;
    }

    if (copy_to_user(buf, data, count)) {
        return -EFAULT;
    }

    return count;
}

ssize_t crypto_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {
    int i;
    //char encrypted_data[1024];
    if (copy_from_user(data, buf, count)) {
        return -EFAULT;
    }

    for (i = 0; i < count; i++) {
        data[i] ^= KEY;
    }

    if (copy_to_user((char *)buf, data, count)) {
        return -EFAULT;
    }

    return count;
}

int crypto_open(struct inode *inode, struct file *filp) {
    return 0;
}

int crypto_release(struct inode *inode, struct file *filp) {
    return 0;
}

static struct file_operations crypto_ops = {
    .owner = THIS_MODULE,
    .read = crypto_read,
    .write = crypto_write,
    .open = crypto_open,
    .release = crypto_release,
};

static int __init crypto_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &crypto_ops);
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

    printk(KERN_INFO "%s: device class created successfully\n", DEVICE_NAME);
    return 0;
}

static void __exit crypto_exit(void) {
    device_destroy(device_class, MKDEV(major_number, 0));
    class_unregister(device_class);
    class_destroy(device_class);
    unregister_chrdev(major_number, DEVICE_NAME);
}

module_init(crypto_init);
module_exit(crypto_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Danil");
MODULE_DESCRIPTION("A simple character device driver for encrypting and decrypting data on the fly");