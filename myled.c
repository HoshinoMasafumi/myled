//SPDX-License-Identifer: GPL-2
// *Copyright (c) 2020 Masafumi Hoshino. All rights reserved..0

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda and Masafumi Hoshino");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

#define sleep_time 500

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

/*
   int morse[36][5] = {//0->short,1->long
//a~m
{0,1},
{1,0,0,0},
{1,0,1,0},
{1,0,0},
{0},
{0,0,1,0},
{1,1,0},
{0,0,0,0},
{0,0},
{0,1,1,1},
{1,0,1},
{0,1,0,0},
{1,1},
//n~z
{1,0},
{1,1,1},
{0,1,1,0},
{1,1,0,1},
{0,1,0},
{0,0,0},
{1},
{0,0,1},
{0,0,0,1},
{0,1,1},
{1,0,0,1},
{1,0,1,1},
{1,1,0,0},
//0~1
{1,1,1,1,1},
{0,1,1,1,1},
{0,0,1,1,1},
{0,0,0,1,1},
{0,0,0,0,1},
{0,0,0,0,0},
{1,0,0,0,0},
{1,1,0,0,0},
{1,1,1,0,0},
{1,1,1,1,0}
};
*/
int short_points(void){
    gpio_base[7] = 1 << 25;
    msleep(250);
    gpio_base[10] = 1 << 25;
    msleep(sleep_time);
    return 0;
}

int long_points(void){
    gpio_base[7] = 1 << 25;
    msleep(750);
    gpio_base[10] = 1 << 25;
    msleep(sleep_time);
    return 0;
}

int select(int a){
    if (a == 0){
        short_points();
    }else if(a == 1){
        long_points();
    }
    return 0;
}

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
    char c;
    int i;
    if(copy_from_user(&c,buf,sizeof(char)))
        return -EFAULT;

    //    printk(KERN_INFO "receive %c\n",c);

    /*
       if(c >='a' && c<='z'){
       for(i=0;i<4;i++){
       if(morse[c-97][i] == NULL) break;
       select(morse[c-97][i]);
       }
       }else{
       for(i=0;i<5;i++){
       select(morse[c][i]);
       }
       }
       */
    if(c == '0'){
        select(1);
        select(1);
        select(1);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == '1'){
        select(0);
        select(1);
        select(1);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == '2'){
        select(0);
        select(0);
        select(1);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == '3'){
        select(0);
        select(0);
        select(0);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == '4'){
        select(0);
        select(0);
        select(0);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == '5'){
        select(0);
        select(0);
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == '6'){
        select(1);
        select(0);
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == '7'){
        select(1);
        select(1);
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == '8'){
        select(1);
        select(1);
        select(1);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == '9'){
        select(1);
        select(1);
        select(1);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'a'){
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'b'){
        select(1);
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 'c'){
        select(1);
        select(0);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'd'){
        select(1);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 'e'){
        select(0);
        msleep(1500);
    }else if(c == 'f'){
        select(0);
        select(0);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'g'){
        select(1);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'h'){
        select(0);
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 'i'){
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 'j'){
        select(0);
        select(1);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == 'k'){
        select(1);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'l'){
        select(0);
        select(1);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 'm'){
        select(1);
        select(1);
        msleep(1500);
    }else if(c == 'n'){
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'o'){
        select(1);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == 'p'){
        select(0);
        select(1);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 'q'){
        select(1);
        select(1);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'r'){
        select(0);
        select(1);
        select(0);
        msleep(1500);
    }else if(c == 's'){
        select(0);
        select(0);
        select(0);
        msleep(1500);
    }else if(c == 't'){
        select(1);
        msleep(1500);
    }else if(c == 'u'){
        select(0);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'v'){
        select(0);
        select(0);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'w'){
        select(0);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == 'x'){
        select(1);
        select(0);
        select(0);
        select(1);
        msleep(1500);
    }else if(c == 'y'){
        select(1);
        select(0);
        select(1);
        select(1);
        msleep(1500);
    }else if(c == 'z'){
        select(1);
        select(1);
        select(0);
        select(0);
        msleep(1500);
    }

    return 1;
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
    int size = 0;
    char sushi[] = {'s', 'u', 's', 'h', 'i', 0x0A};
    if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
        printk(KERN_ERR "sushi : copy_to_user failed\n");
        return -EFAULT;
    }
    size += sizeof(sushi);
    return size;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .read = sushi_read
};

static int __init init_mod(void)
{
    int retval;
    retval = alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){

        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__, MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n",MAJOR(dev), MAJOR(dev));
        return retval;
    }

    cls = class_create(THIS_MODULE, "myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR"class_create failed.");
        return PTR_ERR(cls);
    }

    device_create(cls, NULL,dev, NULL, "myled%d",MINOR(dev));

    gpio_base = ioremap_nocache(0xfe200000,0xA0);

    const u32 led = 25;
    const u32 index = led/10;
    const u32 shift = (led%10)*3;
    const u32 mask = ~(0x7<<shift);
    gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);

    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev,1);
    printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
