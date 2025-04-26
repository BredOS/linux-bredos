/*
 * Copyright (C) 2014 Rockchip Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/platform_device.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/debugfs.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/iio/consumer.h>
#include <linux/kthread.h>


static unsigned int mobile_power_f = 0;
static unsigned int mobile_power = 0;
static unsigned int mobile_reset = 0;
static unsigned int mobile_w_disable = 0;

static int jw_io_control_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	enum of_gpio_flags flags;

	/*----------------------mobile gpio init start---------------------------------------*/
	//mobile_power_f
	mobile_power_f = of_get_named_gpio_flags(node, "mobile_power_f", 0, &flags);
	devm_gpio_request(&pdev->dev, mobile_power_f, "mobile_power_f");
	gpio_direction_output(mobile_power_f,1);
	msleep(100);
	//mobile_reset
	mobile_reset = of_get_named_gpio_flags(node, "mobile_reset", 0, &flags);
	devm_gpio_request(&pdev->dev, mobile_reset, "mobile_reset");
	gpio_direction_output(mobile_reset,0);
	msleep(100);
	//mobile_power
	mobile_power = of_get_named_gpio_flags(node, "mobile_power", 0, &flags);
	devm_gpio_request(&pdev->dev, mobile_power, "mobile_power");
	gpio_direction_output(mobile_power,1);
	msleep(100);
	//mobile_w_disable
	mobile_w_disable = of_get_named_gpio_flags(node, "mobile_w_disable", 0, &flags);
	devm_gpio_request(&pdev->dev, mobile_w_disable, "mobile_w_disable");
	gpio_direction_output(mobile_w_disable,1);
	msleep(100);
	gpio_direction_output(mobile_reset,1);
	msleep(100);
	/*----------------------mobile gpio init end---------------------------------------*/

	printk("jw_io_control_probe ok\n");

	return 0;
}

static void jw_io_shutdown(struct platform_device *dev)
{
}

static int jw_io_resume(struct platform_device *dev)
{
	return 0;
}

static int jw_io_suspend(struct platform_device *dev, pm_message_t state)
{
	return 0;
}

static const struct of_device_id jw_io_control_of_match[] = {
        { .compatible = "jw_io_control", },
        {},
};
MODULE_DEVICE_TABLE(of, jw_io_control_of_match);

static struct platform_driver jw_io_control_driver = {
	.probe		= jw_io_control_probe,
	.shutdown	= jw_io_shutdown,
	.resume		= jw_io_resume,
	.suspend	= jw_io_suspend,
	.driver	= {
		.name	= "jw_io_control",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(jw_io_control_of_match),
	},
};
/*
static int __init jw_io_control_init(void)
{
	platform_driver_register(&jw_io_control_driver);
	return 0;
}

static void __exit jw_io_control_exit(void)
{
	platform_driver_unregister(&jw_io_control_driver);
}
*/
module_platform_driver(jw_io_control_driver);
MODULE_ALIAS("platform:jw_io_control");
MODULE_AUTHOR("Bin Yang <yangbin@rock-chips.com>");
MODULE_DESCRIPTION("USB modem GPIO Driver");
MODULE_LICENSE("GPL");
