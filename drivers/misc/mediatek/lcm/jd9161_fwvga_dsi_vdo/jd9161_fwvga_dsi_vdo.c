/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
#ifdef BUILD_LK
#else
#include <linux/string.h>
#endif

#include "lcm_drv.h"



// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(480)
#define FRAME_HEIGHT 										(854)

#define REGFLAG_DELAY             							0XFFE
#define REGFLAG_END_OF_TABLE      							0xFFF   // END OF REGISTERS MARKER

#define LCM_ID_JD9161										(0x9161)

#define JD9161_HSD_SANLONG

//#define JD9161_ZHONGGUANGDIAN  //wangsl
// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg											lcm_util.dsi_read_reg()
#define read_reg_v2(cmd, buffer, buffer_size)				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_initialization_setting[] = {
#if defined(JD9161_HELITAI)
//#error ************************000000000000000000000*************************
 //JD9161 HELITAI HSD4.5 S11 CF12
{0xBF,3,{0x91,0x61,0xF2}},
{0xB3,2,{0x00,0x87}},
{0xB4,2,{0x00,0x87}},
{0xB8,6,{0x00,0xBF,0x20,0x00,0xBF,0x20}},
{0xBA,3,{0x34,0x23,0x00}},
{0xC3,1,{0x02}},
{0xC4,2,{0x30,0x6A}},
{0xC7,9,{0x00,0x01,0x31,0x0A,0x6A,0x2A,0x13,0xA5,0xA5}},
{0xC8,38,{0x7E,0x5F,0x49,0x37,0x2B,0x1A,0x1D,0x06,0x20,0x20,0x21,0x43,0x36,0x45,0x3E,0x44,0x3E,0x35,0x27,0x7E,0x5F,0x49,0x37,0x2B,0x1A,0x1D,0x06,0x20,0x20,0x21,0x43,0x36,0x45,0x3E,0x44,0x3E,0x35,0x27}},
{0xD4,16,{0x1E,0x1F,0x17,0x37,0x06,0x04,0x0A,0x08,0x00,0x02,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD5,16,{0x1E,0x1F,0x17,0x37,0x07,0x05,0x0B,0x09,0x01,0x03,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD6,16,{0x1F,0x1E,0x17,0x17,0x07,0x09,0x0B,0x05,0x03,0x01,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD7,16,{0x1F,0x1E,0x17,0x17,0x06,0x08,0x0A,0x04,0x02,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD8,20,{0x20,0x00,0x00,0x30,0x03,0x30,0x01,0x02,0x00,0x01,0x02,0x06,0x70,0x00,0x00,0x73,0x07,0x06,0x70,0x08}},
{0xD9,19,{0x00,0x0A,0x0A,0x80,0x00,0x00,0x06,0x7B,0x00,0x80,0x00,0x33,0x6A,0x1F,0x00,0x00,0x00,0x03,0x7B}},
{0x11,1,{00}},                 // Sleep-Out
{REGFLAG_DELAY, 120, {}},
{0x29,1,{00}},                 // Display On
{REGFLAG_DELAY, 50, {}},
{REGFLAG_END_OF_TABLE, 0x00, {}}

#elif defined(JD9161_HSD_SANLONG)
//#error:***************JD9161_HSD_SANLONG********************
 //JD9161 SANLONG TT KS5004F
{0xBF,3,{0x91,0x61,0xF2}},
{0xB3,2,{0x00,0x87}},
{0xB4,2,{0x00,0x87}},
{0xB8,6,{0x00,0xBF,0x20,0x00,0xBF,0x20}},
{0xBA,3,{0x34,0x23,0x00}},
{0xC3,1,{0x02}},
{0xC4,2,{0x30,0x6A}},
{0xC7,9,{0x00,0x01,0x31,0x0A,0x6A,0x2A,0x13,0xA5,0xA5}},
{0xC8,38,{0x7E,0x5F,0x49,0x37,0x2B,0x1A,0x1D,0x06,0x20,0x20,0x21,0x43,0x36,0x45,0x3E,0x44,0x3E,0x35,0x27,0x7E,0x5F,0x49,0x37,0x2B,0x1A,0x1D,0x06,0x20,0x20,0x21,0x43,0x36,0x45,0x3E,0x44,0x3E,0x35,0x27}},
{0xD4,16,{0x1E,0x1F,0x17,0x37,0x06,0x04,0x0A,0x08,0x00,0x02,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD5,16,{0x1E,0x1F,0x17,0x37,0x07,0x05,0x0B,0x09,0x01,0x03,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD6,16,{0x1F,0x1E,0x17,0x17,0x07,0x09,0x0B,0x05,0x03,0x01,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD7,16,{0x1F,0x1E,0x17,0x17,0x06,0x08,0x0A,0x04,0x02,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD8,20,{0x20,0x00,0x00,0x30,0x03,0x30,0x01,0x02,0x00,0x01,0x02,0x06,0x70,0x00,0x00,0x73,0x07,0x06,0x70,0x08}},
{0xD9,19,{0x00,0x0A,0x0A,0x80,0x00,0x00,0x06,0x7B,0x00,0x80,0x00,0x33,0x6A,0x1F,0x00,0x00,0x00,0x03,0x7B}},
{0x11,1,{00}},                 // Sleep-Out
{REGFLAG_DELAY, 120, {}},
{0x29,1,{00}},                 // Display On
{REGFLAG_DELAY, 50, {}},
{REGFLAG_END_OF_TABLE, 0x00, {}}

#elif defined(JD9161_ZHONGGUANGDIAN)  //JD9161_ZHONGGUANGDIAN BOE4.5 S11 TRX W456
//#error ************************1111111111111*************************
{0xBF,3,{0x91,0x61,0xF2}},
{0xB3,2,{0x00,0xA6}},
{0xB4,2,{0x00,0x7F}},
{0xB8,6,{0x00,0x9F,0x01,0x00,0x9F,0x01}},
{0xBA,3,{0x34,0x23,0x00}},
{0xC3,1,{0x02}},
{0xC4,2,{0x30,0x6A}},
{0xC7,9,{0x00,0x01,0x31,0x05,0x65,0x2C,0x13,0xA5,0xA5}},
{0xC8,38,{0x7C,0x6B,0x5E,0x53,0x51,0x42,0x47,0x2F,0x45,0x41,0x3E,0x5A,0x47,0x4D,0x3E,0x32,0x1F,0x0E,0x03,0x7C,0x6B,0x5E,0x53,0x51,0x42,0x47,0x2F,0x45,0x41,0x3E,0x5A,0x47,0x4D,0x3E,0x32,0x1F,0x0E,0x03}},
{0xD4,16,{0x1F,0x1E,0x05,0x07,0x01,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD5,16,{0x1F,0x1E,0x04,0x06,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD6,16,{0x1F,0x1F,0x06,0x04,0x00,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD7,16,{0x1F,0x1F,0x07,0x05,0x01,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F}},
{0xD8,20,{0x20,0x00,0x00,0x10,0x03,0x20,0x01,0x02,0x00,0x01,0x02,0x5F,0x5F,0x00,0x00,0x32,0x04,0x5F,0x5F,0x08}},
{0xD9,19,{0x00,0x0A,0x0A,0x88,0x00,0x00,0x06,0x7b,0x00,0x00,0x00,0x3B,0x2F,0x1F,0x00,0x00,0x00,0x03,0x7B}},
{0xBE,1,{0x01}},
{0xEB,1,{0xF6}},
{0xBE,1,{0x00}},
{0xBE,1,{0x01}},
{0xCC,10,{0x34,0x20,0x38,0x60,0x11,0x91,0x00,0x40,0x00,0x00}},
{0xBE,1,{0x00}},
{0x55,1,{0x90}},
{0x11,1,{0x00}},                 // Sleep-Out
{REGFLAG_DELAY, 120, {}},
{0x29,1,{0x00}},                 // Display On
{REGFLAG_DELAY, 10, {}},
{REGFLAG_END_OF_TABLE, 0x00, {}}

#else	
//#error ***********************22222222222222222222222*************************	
 //JD9161 JINGTAI IVO4.5 S11 CF12
 
{0xBF,3,{0x91,0x61,0xF2}},
 
{0xB3,2,{0x00,0x9d}}, 
 
{0xB4,2,{0x00,0x9d}}, 
 
{0xB8,6,{0x00,0x9F,0x01,0x00,0x9F,0x01}},
 
{0xBA,3,{0x3E,0x23,0x00}}, 

{0xC3,1,{0x01}},
 
{0xC4,2,{0x30,0x6A}}, 
 
{0xC7,9,{0x00,0x01,0x31,0x0A,0x6A,0x2A,0x13,0xA5,0xA5}}, 

{0xC8,38,{0x7F,0x7B,0x73,0x68,0x5A,0x40,0x38,0x1C,0x34,0x33,
          0x35,0x58,0x4C,0x5D,0x56,0x5D,0x58,0x51,0x48,0x7F,
          0x7B,0x73,0x68,0x5A,0x40,0x38,0x1C,0x34,0x33,0x35,
          0x58,0x4C,0x5D,0x56,0x5D,0x58,0x51,0x48}}, 
 
{0xD4,16,{0x1F,0x1F,0x1F,0x03,0x01,0x05,0x07,0x09,0x0B,0x11,
          0x13,0x1F,0x1F,0x1F,0x1F,0x1F}}, 
 
{0xD5,16,{0x1F,0x1F,0x1F,0x02,0x00,0x04,0x06,0x08,0x0A,0x10,
          0x12,0x1F,0x1F,0x1F,0x1F,0x1F}}, 
 
{0xD6,16,{0x1F,0x1F,0x1F,0x10,0x12,0x04,0x0A,0x08,0x06,0x02,
          0x00,0x1F,0x1F,0x1F,0x1F,0x1F}},
 
{0xD7,16,{0x1F,0x1F,0x1F,0x11,0x13,0x05,0x0B,0x09,0x07,0x03,
          0x01,0x1F,0x1F,0x1F,0x1F,0x1F}}, 
 
{0xD8,20,{0x20,0x00,0x00,0x30,0x03,0x30,0x01,0x02,0x30,0x01,
          0x02,0x06,0x70,0x73,0x5D,0x73,0x06,0x06,0x70,0x08}}, 
 
{0xD9,19,{0x00,0x0A,0x0A,0x88,0x00,0x00,0x06,0x7B,0x00,0x80,
          0x00,0x3B,0x33,0x1F,0x00,0x00,0x00,0x06,0x70}},
		  
{0x11,1,{00}},                 // Sleep-Out
{REGFLAG_DELAY, 120, {}},
{0x29,1,{00}},                 // Display On
{REGFLAG_DELAY, 50, {}},
{REGFLAG_END_OF_TABLE, 0x00, {}}
#endif
};

#if 0
static struct LCM_setting_table lcm_sleep_out_setting[] = {

	// Sleep Out
	{0x11, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	// Display ON
	{0x29, 0, {0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif

static struct LCM_setting_table lcm_deep_sleep_in_setting[] = {

#if 1
	/* Sleep Mode On */
	{ 0x10, 0, {} },
	{ REGFLAG_DELAY, 120, {} },
	{ REGFLAG_END_OF_TABLE, 0x00, {} }
#else
	// Display off sequence
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 20, {}},
	// Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
#endif
};
static struct LCM_setting_table lcm_prepare_setting[] = {
    {0xBF, 3, {0x91,0x61,0xF2}}, // page 1
	  {REGFLAG_END_OF_TABLE, 0x00, {}}	
};

static unsigned int lcm_compare_id(void);

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;
	
	for(i = 0; i < count; i++) {
		unsigned cmd;
		cmd = table[i].cmd;
		
		switch (cmd) {	
		case REGFLAG_DELAY :
			MDELAY(table[i].count);
			break;
		case REGFLAG_END_OF_TABLE :
			break;
		default:
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}
}

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));
	
	params->type   = LCM_TYPE_DSI; 
	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	
	params->dsi.mode   = BURST_VDO_MODE;
	params->dsi.LANE_NUM				= LCM_TWO_LANE;
	
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq	  = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding 	  = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format	    = LCM_DSI_FORMAT_RGB888;
	
	// Video mode setting		
	params->dsi.intermediat_buffer_num = 2;
	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.word_count=FRAME_WIDTH*3;	//DSI CMD mode need set these two bellow params, different to 6577
	params->dsi.vertical_active_line=FRAME_HEIGHT;      

#if defined(JD9161_HELITAI)
  params->dsi.vertical_sync_active                                = 3;//4;   //3   
  params->dsi.vertical_backporch                                  = 11;//6;   //6 //
  params->dsi.vertical_frontporch                                 = 20;//6;    //20

#elif defined(JD9161_HSD_SANLONG)
  params->dsi.vertical_sync_active                                = 3;//4;   //3   
  params->dsi.vertical_backporch                                  = 11;//6;   //6 //
  params->dsi.vertical_frontporch                                 = 20;//6;    //20

#elif defined(JD9161_ZHONGGUANGDIAN)
  params->dsi.vertical_sync_active                                = 4;//4;   //4
  params->dsi.vertical_backporch                                  = 6;//6;   //6 
  params->dsi.vertical_frontporch                                 = 10;//6;    //10

#else
  params->dsi.vertical_sync_active                                = 3;//4;   //3
  params->dsi.vertical_backporch                                  = 8;//6;   //6 //7
  params->dsi.vertical_frontporch                                 = 20;//6;    //20
#endif  


	params->dsi.vertical_active_line				= FRAME_HEIGHT;	
	params->dsi.horizontal_sync_active				= 10; //10
	params->dsi.horizontal_backporch				= 50; //50
	params->dsi.horizontal_frontporch				= 50; //50 
	
	params->dsi.horizontal_blanking_pixel				= 60;
	params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
	params->dsi.compatibility_for_nvk = 0;		// this parameter would be set to 1 if DriverIC is NTK's and when force match DSI clock for NTK's

	params->dsi.PLL_CLOCK = 208;//208
	params->dsi.ssc_range =0; 
	params->dsi.ssc_disable = 1; 
	
	#if 1
	params->dsi.esd_check_enable = 0;
	#else
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd          = 0x0A;
	params->dsi.lcm_esd_check_table[0].count        = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;
	#endif
}

static void lcm_init(void)
{
	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(10);
	
	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	push_table(lcm_deep_sleep_in_setting, sizeof(lcm_deep_sleep_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
#if 1
	MDELAY(10);
	lcm_init();
	MDELAY(10);
#else
    push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
#endif

}

static unsigned int lcm_compare_id(void)
{
	unsigned int array[4];
	unsigned short device_id;
	unsigned char buffer[2];
	//return 1;
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(100);
	
	
    push_table(lcm_prepare_setting, sizeof(lcm_prepare_setting) / sizeof(struct LCM_setting_table), 1);

    //*************Enable CMD2 Page1  *******************//
	array[0] = 0x00033700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x04, buffer, 3);
	device_id = buffer[0]<<8|buffer[1];

	//return 1;
	return (LCM_ID_JD9161 == device_id) ? 1 : 0;
}

LCM_DRIVER jd9161_fwvga_dsi_vdo = 
{
	.name		= "jd9161_fwvga_dsi_vdo",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
};
