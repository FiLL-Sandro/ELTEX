#include <linux/cdev.h>
#include "../dev.h"

static int major = 0;
module_param( major, int, S_IRUGO );

#define EOK 0
static int device_open = 0;

static int dev_open( struct inode *n, struct file *f ) {
   if( device_open ) return -EBUSY;
   device_open++;
   return EOK;
}

static int dev_release( struct inode *n, struct file *f ) {
   device_open--;
   return EOK;
}

static const struct file_operations dev_fops = {
   .owner = THIS_MODULE,
   .open = dev_open,
   .release = dev_release,
   .read  = dev_read,
};

#define DEVICE_FIRST  0
#define DEVICE_COUNT  3
#define MODNAME "my_cdev_dev"

static struct cdev hcdev;

static int __init dev_init( void ) {
/*
* В начале идёт захват региона, т.е. попытка получить ряд major- и 
* minor-номеров;
* major может быть указан в параметрах, а потому возможен отсчёт от этого 
* значения; если он не был указан, то будет проведено динамический захват;
*/

   int ret;
   dev_t dev;
   if( major != 0 ) {
      dev = MKDEV( major, DEVICE_FIRST );  //формирование major- и minor- номеров
      ret = register_chrdev_region( dev, DEVICE_COUNT, MODNAME ); //захват региона
   }
   else {
      ret = alloc_chrdev_region( &dev, DEVICE_FIRST, DEVICE_COUNT, MODNAME );// динамический захват региона
      major = MAJOR( dev );  // запоминание динамически выделенного major-номера
   }
   //Далее идёт проверка на ошибки при захвате региона
   if( ret < 0 ) {
      printk( KERN_ERR "=== Can not register char device region\n" );
      goto err;
   }

   cdev_init( &hcdev, &dev_fops );  //инициализация struct cdev
   hcdev.owner = THIS_MODULE;
   ret = cdev_add( &hcdev, dev, DEVICE_COUNT ); //добавление устройства в систему
   if( ret < 0 ) {  //Далее идёт проверка на ошибки при добавлении устройства
      unregister_chrdev_region( MKDEV( major, DEVICE_FIRST ), DEVICE_COUNT );
      printk( KERN_ERR "=== Can not add char device\n" );
      goto err;
   }
   printk( KERN_INFO "=========== module installed %d:%d ==============\n",
           MAJOR( dev ), MINOR( dev ) );
err:
   return ret;
}

static void __exit dev_exit( void ) {
   cdev_del( &hcdev );  //исключение устройства из системы
   unregister_chrdev_region( MKDEV( major, DEVICE_FIRST ), DEVICE_COUNT ); //освобождение major- и minor- номеров
   printk( KERN_INFO "=============== module removed ==================\n" );
}
