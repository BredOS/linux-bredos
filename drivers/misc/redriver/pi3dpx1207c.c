// SPDX-License-Identifier: GPL-2.0-only
/*
 * Haoyu pi3dpx1207c RTC driver
 *
 * Copyright (C) 2013 MundoReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * based on rtc-pi3dpx1207c
 * Copyright (C) 2010 ROCKCHIP, Inc.
 */

#include <linux/module.h>
#include <linux/clk-provider.h>
#include <linux/i2c.h>
#include <linux/usb/typec_dp.h>
#define PI3DPX_BYTES_NUM	9

extern int redriver_reg_notifier(struct notifier_block *nb);
extern void redriver_unreg_notifier(struct notifier_block *nb);

struct pi3dpx_config {
    uint8_t full_dp_config[9];
		uint8_t no_dp_config[9];
		uint8_t usb_dp_config[9];
};

struct pi3dpx_priv {
    struct i2c_client       *client;
		struct notifier_block nb;
    unsigned long typec_state;
    unsigned int flip;
};

struct pi3dpx_config redriver_config[2] = {
	{
		{0x13 ,0x11 ,0x20 ,0x22 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
		{0x13 ,0x11 ,0x20 ,0x42 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
		{0x13 ,0x11 ,0x20 ,0x62 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
	},

	{
		{0x13 ,0x11 ,0x20 ,0x32 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
		{0x13 ,0x11 ,0x20 ,0x52 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
		{0x13 ,0x11 ,0x20 ,0x82 ,0x00 ,0xa7 ,0xa7 ,0xa7 ,0xa7},
	}

};
static int pi3dpx_i2c_write(struct pi3dpx_priv *priv,int bytes, void *src)
{
   struct i2c_client *i2c = priv->client;
   struct i2c_msg msg;
   int ret;
   if (bytes != PI3DPX_BYTES_NUM)
           return -EINVAL;
   msg.addr = i2c->addr;
   msg.flags = 0;
   msg.len = bytes;
   msg.buf = (u8*)src;

   ret = i2c_transfer(i2c->adapter, &msg, 1);
   if (ret != 1)
     dev_err(&i2c->dev, "i2c trasfer error:%d", ret);
   return 0;
}

static int pi3dpx_notifier_call(struct notifier_block *nb,
                unsigned long val, void *v)
{

	unsigned int *flip = (unsigned int*)v;
  struct pi3dpx_priv *priv =
                container_of(nb, struct pi3dpx_priv, nb);
  if ((val == priv->typec_state) && (*flip == priv->flip))
    return NOTIFY_OK;
  priv->typec_state = val;
  priv->flip = *flip;
  pr_info("typec state:%lu, flip:%d", priv->typec_state, priv->flip);
	switch (priv->typec_state) {
		case TYPEC_DP_STATE_E:
    case TYPEC_DP_STATE_C:
			pi3dpx_i2c_write(priv, 9, &redriver_config[0].full_dp_config);
			break;
	  case TYPEC_DP_STATE_D:
			pi3dpx_i2c_write(priv, 9, &redriver_config[priv->flip].usb_dp_config);
		  break;
    default:
      pi3dpx_i2c_write(priv, 9, &redriver_config[priv->flip].no_dp_config);
	}
  return NOTIFY_OK;
}

static int pi3dpx1207c_probe(struct i2c_client *i2c,
			 const struct i2c_device_id *id)
{
  	int ret;
    struct pi3dpx_priv *priv;

    priv = devm_kzalloc(&i2c->dev,
                            sizeof(struct pi3dpx_priv), GFP_KERNEL);
    if (priv == NULL)
       return -ENOMEM;

    i2c_set_clientdata(i2c, priv);
    priv->client = i2c;
    priv->nb.notifier_call = pi3dpx_notifier_call;
    ret = redriver_reg_notifier(&priv->nb);

	return 0;
}

static const struct i2c_device_id pi3dpx1207c_id[] = {
	{ "pi3dpx1207c", 0 },
	{},
};
MODULE_DEVICE_TABLE(i2c, pi3dpx1207c_id);

static const struct of_device_id pi3dpx1207c_dt_idtable[] = {
	{ .compatible = "diodes,pi3dpx1207c" },
	{},
};
MODULE_DEVICE_TABLE(of, pi3dpx1207c_dt_idtable);

static struct i2c_driver pi3dpx1207c_driver = {
	.driver		= {
		.name	= "pi3dpx1207c",
		.of_match_table	= pi3dpx1207c_dt_idtable,
	},
	.probe		= pi3dpx1207c_probe,
	.id_table	= pi3dpx1207c_id,
};

module_i2c_driver(pi3dpx1207c_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("pi3dpx1207c redriver driver");
MODULE_LICENSE("GPL");
