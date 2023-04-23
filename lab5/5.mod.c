#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe63d5a03, "module_layout" },
	{ 0x37a0cba, "kfree" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0x9d656b88, "class_unregister" },
	{ 0x9529a8b0, "device_destroy" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xb298edeb, "class_destroy" },
	{ 0x5f504c5f, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4a253998, "__class_create" },
	{ 0xc5850110, "printk" },
	{ 0x32d48119, "__register_chrdev" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x14994725, "kmem_cache_alloc_trace" },
	{ 0x6104427f, "kmalloc_caches" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x754d539c, "strlen" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "41A842CB6288FE5D558F5ED");
