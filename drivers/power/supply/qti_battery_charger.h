// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2021, Qualcomm Innovation Center, Inc. All rights reserved.
 * Copyright (c) 2022-2023, The LineageOS Project. All rights reserved.
 */

#define MSG_OWNER_BC			32778
#define MSG_TYPE_REQ_RESP		1
#define MSG_TYPE_NOTIFY			2

/* opcode for battery charger */
#define BC_SET_NOTIFY_REQ		0x04
#define BC_DISABLE_NOTIFY_REQ		0x05
#define BC_NOTIFY_IND			0x07
#define BC_BATTERY_STATUS_GET		0x30
#define BC_BATTERY_STATUS_SET		0x31
#define BC_USB_STATUS_GET		0x32
#define BC_USB_STATUS_SET		0x33
#define BC_WLS_STATUS_GET		0x34
#define BC_WLS_STATUS_SET		0x35
#define BC_SHIP_MODE_REQ_SET		0x36
#define BC_SHUTDOWN_REQ_SET		0x37
#define BC_WLS_FW_CHECK_UPDATE		0x40
#define BC_WLS_FW_PUSH_BUF_REQ		0x41
#define BC_WLS_FW_UPDATE_STATUS_RESP	0x42
#define BC_WLS_FW_PUSH_BUF_RESP		0x43
#define BC_WLS_FW_GET_VERSION		0x44
#define BC_SHUTDOWN_NOTIFY		0x47
#define BC_HBOOST_VMAX_CLAMP_NOTIFY	0x79
#define BC_GENERIC_NOTIFY		0x80
#define BC_XM_STATUS_GET		0x50
#define BC_XM_STATUS_SET		0x51

/* Generic definitions */
#define MAX_STR_LEN			128
#define BC_WAIT_TIME_MS			1000
#define WLS_FW_PREPARE_TIME_MS		1000
#define WLS_FW_WAIT_TIME_MS		500
#define WLS_FW_UPDATE_TIME_MS		1000
#define WLS_FW_BUF_SIZE			128
#define DEFAULT_RESTRICT_FCC_UA		1000000
#define CHG_DEBUG_DATA_LEN		200

#if defined(CONFIG_BQ_FG_2S)
#define BATTERY_DIGEST_LEN 20
#else
#define BATTERY_DIGEST_LEN 32
#endif
#define BATTERY_SS_AUTH_DATA_LEN 4
#define USBPD_UVDM_SS_LEN		4
#define USBPD_UVDM_VERIFIED_LEN		1

#define MAX_THERMAL_LEVEL		16

enum uvdm_state {
	USBPD_UVDM_DISCONNECT,
	USBPD_UVDM_CHARGER_VERSION,
	USBPD_UVDM_CHARGER_VOLTAGE,
	USBPD_UVDM_CHARGER_TEMP,
	USBPD_UVDM_SESSION_SEED,
	USBPD_UVDM_AUTHENTICATION,
	USBPD_UVDM_VERIFIED,
	USBPD_UVDM_REMOVE_COMPENSATION,
	USBPD_UVDM_REVERSE_AUTHEN,
	USBPD_UVDM_CONNECT,
};

enum usb_connector_type {
	USB_CONNECTOR_TYPE_TYPEC,
	USB_CONNECTOR_TYPE_MICRO_USB,
};

enum psy_type {
	PSY_TYPE_BATTERY,
	PSY_TYPE_USB,
	PSY_TYPE_WLS,
	PSY_TYPE_XM,
	PSY_TYPE_MAX,
};

enum ship_mode_type {
	SHIP_MODE_PMIC,
	SHIP_MODE_PACK_SIDE,
};

/* property ids */
enum battery_property_id {
	BATT_STATUS,
	BATT_HEALTH,
	BATT_PRESENT,
	BATT_CHG_TYPE,
	BATT_CAPACITY,
	BATT_SOH,
	BATT_VOLT_OCV,
	BATT_VOLT_NOW,
	BATT_VOLT_MAX,
	BATT_CURR_NOW,
	BATT_CHG_CTRL_LIM,
	BATT_CHG_CTRL_LIM_MAX,
	BATT_CONSTANT_CURRENT,
	BATT_TEMP,
	BATT_TECHNOLOGY,
	BATT_CHG_COUNTER,
	BATT_CYCLE_COUNT,
	BATT_CHG_FULL_DESIGN,
	BATT_CHG_FULL,
	BATT_MODEL_NAME,
	BATT_TTF_AVG,
	BATT_TTE_AVG,
	BATT_RESISTANCE,
	BATT_POWER_NOW,
	BATT_POWER_AVG,
	BATT_PROP_MAX,
};

enum usb_property_id {
	USB_ONLINE,
	USB_VOLT_NOW,
	USB_VOLT_MAX,
	USB_CURR_NOW,
	USB_CURR_MAX,
	USB_INPUT_CURR_LIMIT,
	USB_TYPE,
	USB_ADAP_TYPE,
	USB_MOISTURE_DET_EN,
	USB_MOISTURE_DET_STS,
	USB_TEMP,
	USB_REAL_TYPE,
	USB_TYPEC_COMPLIANT,
	USB_SCOPE,
	USB_CONNECTOR_TYPE,
	F_ACTIVE,
	USB_PROP_MAX,
};

enum wireless_property_id {
	WLS_ONLINE,
	WLS_VOLT_NOW,
	WLS_VOLT_MAX,
	WLS_CURR_NOW,
	WLS_CURR_MAX,
#ifndef CONFIG_MI_WLS_REVERSE_CHG_ONLY
	WLS_TYPE,
#endif
	WLS_BOOST_EN,
#ifndef CONFIG_MI_WLS_REVERSE_CHG_ONLY
	WLS_HBOOST_VMAX,
	WLS_INPUT_CURR_LIMIT,
	WLS_ADAP_TYPE,
	WLS_CONN_TEMP,
#endif
	WLS_PROP_MAX,
};

enum xm_property_id {
	XM_PROP_RESISTANCE_ID,
	XM_PROP_VERIFY_DIGEST,
	XM_PROP_CONNECTOR_TEMP,
	XM_PROP_AUTHENTIC,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_BATTERY_ADAPT_POWER_MATCH,
#endif /* !CONFIG_MI_CHARGER_M81 */
	XM_PROP_CHIP_OK,
	XM_PROP_VBUS_DISABLE,
	XM_PROP_REAL_TYPE,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_THERMAL_BOARD_TEMP,
#endif /* !CONFIG_MI_CHARGER_M81 */
	/*used for pd authentic*/
	XM_PROP_VERIFY_PROCESS,
	XM_PROP_VDM_CMD_CHARGER_VERSION,
	XM_PROP_VDM_CMD_CHARGER_VOLTAGE,
	XM_PROP_VDM_CMD_CHARGER_TEMP,
	XM_PROP_VDM_CMD_SESSION_SEED,
	XM_PROP_VDM_CMD_AUTHENTICATION,
	XM_PROP_VDM_CMD_VERIFIED,
	XM_PROP_VDM_CMD_REMOVE_COMPENSATION,
	XM_PROP_VDM_CMD_REVERSE_AUTHEN,
	XM_PROP_CURRENT_STATE,
	XM_PROP_ADAPTER_ID,
	XM_PROP_ADAPTER_SVID,
	XM_PROP_PD_VERIFED,
	XM_PROP_PDO2,
	XM_PROP_UVDM_STATE,
	/*charger_pump sys node*/
	XM_PROP_BQ2597X_CHIP_OK,
	XM_PROP_BQ2597X_SLAVE_CHIP_OK,
	XM_PROP_BQ2597X_BUS_CURRENT,
	XM_PROP_BQ2597X_SLAVE_BUS_CURRENT,
	XM_PROP_BQ2597X_BUS_DELTA,
	XM_PROP_BQ2597X_BUS_VOLTAGE,
	XM_PROP_BQ2597X_BATTERY_PRESENT,
	XM_PROP_BQ2597X_SLAVE_BATTERY_PRESENT,
	XM_PROP_BQ2597X_BATTERY_VOLTAGE,
	XM_PROP_MASTER_SMB1396_ONLINE,
	XM_PROP_MASTER_SMB1396_IIN,
	XM_PROP_SLAVE_SMB1396_ONLINE,
	XM_PROP_SLAVE_SMB1396_IIN,
	XM_PROP_SMB_IIN_DIFF,
	XM_PROP_CC_ORIENTATION,
	XM_PROP_INPUT_SUSPEND,
	XM_PROP_FASTCHGMODE,
	XM_PROP_NIGHT_CHARGING,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_BLANK_STATUS,
	XM_PROP_SCREEN_CCTOG,
#endif /* !CONFIG_MI_CHARGER_M81 */
	XM_PROP_SOC_DECIMAL,
	XM_PROP_SOC_DECIMAL_RATE,
	XM_PROP_QUICK_CHARGE_TYPE,
	XM_PROP_APDO_MAX,
	XM_PROP_POWER_MAX,
	XM_PROP_DIE_TEMPERATURE,
	XM_PROP_SLAVE_DIE_TEMPERATURE,
	XM_PROP_FG_RAW_SOC,
	/* wireless charge infor */
#ifdef CONFIG_MI_CHARGER_M81
	XM_PROP_WLS_START = 50,
#else
	XM_PROP_WLS_START,
#endif /* CONFIG_MI_CHARGER_M81 */
	XM_PROP_TX_MACL,
	XM_PROP_TX_MACH,
	XM_PROP_PEN_MACL,
	XM_PROP_PEN_MACH,
	XM_PROP_TX_IOUT,
	XM_PROP_TX_VOUT,
	XM_PROP_PEN_SOC,
	XM_PROP_PEN_HALL3,
	XM_PROP_PEN_HALL4,
	XM_PROP_RX_CRL,
	XM_PROP_RX_CRH,
	XM_PROP_RX_CEP,
	XM_PROP_BT_STATE,
	XM_PROP_REVERSE_CHG_MODE,
	XM_PROP_REVERSE_CHG_STATE,
	XM_PROP_RX_VOUT,
	XM_PROP_RX_VRECT,
	XM_PROP_RX_IOUT,
	XM_PROP_TX_ADAPTER,
	XM_PROP_OP_MODE,
	XM_PROP_WLS_DIE_TEMP,
	XM_PROP_WLS_BIN,
	XM_PROP_WLSCHARGE_CONTROL_LIMIT,
	XM_PROP_FW_VER,
	XM_PROP_WLS_THERMAL_REMOVE,
	XM_PROP_CHG_DEBUG,
	XM_PROP_WLS_FW_STATE,
	XM_PROP_WLS_CAR_ADAPTER,
	XM_PROP_WLS_TX_SPEED,
	XM_PROP_WLS_FC_FLAG,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_WLS_END,
#endif /* !CONFIG_MI_CHARGER_M81 */
	/**********************/
	XM_PROP_SHUTDOWN_DELAY,
	XM_PROP_FAKE_TEMP,
	XM_PROP_THERMAL_REMOVE,
	XM_PROP_TYPEC_MODE,
	XM_PROP_MTBF_CURRENT,
	XM_PROP_THERMAL_TEMP,
	XM_PROP_FB_BLANK_STATE,
	XM_PROP_SMART_BATT,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_SMART_CHG,
#endif /* !CONFIG_MI_CHARGER_M81 */
	XM_PROP_SHIPMODE_COUNT_RESET,
	XM_PROP_SPORT_MODE,
	XM_PROP_BATT_CONNT_ONLINE,
	XM_PROP_FAKE_CYCLE,
	XM_PROP_FAKE_SOH,
	XM_PROP_DELTAFV,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_OTG_UI_SUPPORT,
	XM_PROP_CID_STATUS,
	XM_PROP_CC_TOGGLE,
	XM_PROP_HIFI_CONNECT,
#endif /* !CONFIG_MI_CHARGER_M81 */
#ifdef CONFIG_MI_CHARGER_M81
	XM_PROP_CYCLE_COUNT_DIFF,
#endif /* CONFIG_MI_CHARGER_M81 */
	/*********nvt fuelgauge feature*********/
	XM_PROP_NVTFG_MONITOR_ISC,
	XM_PROP_NVTFG_MONITOR_SOA,
	XM_PROP_OVER_PEAK_FLAG,
	XM_PROP_CURRENT_DEVIATION,
	XM_PROP_POWER_DEVIATION,
	XM_PROP_AVERAGE_CURRENT,
	XM_PROP_AVERAGE_TEMPERATURE,
	XM_PROP_START_LEARNING,
	XM_PROP_STOP_LEARNING,
	XM_PROP_SET_LEARNING_POWER,
	XM_PROP_GET_LEARNING_POWER,
	XM_PROP_GET_LEARNING_POWER_DEV,
	XM_PROP_GET_LEARNING_TIME_DEV,
	XM_PROP_SET_CONSTANT_POWER,
	XM_PROP_GET_REMAINING_TIME,
	XM_PROP_SET_REFERANCE_POWER,
	XM_PROP_GET_REFERANCE_CURRENT,
	XM_PROP_GET_REFERANCE_POWER,
	XM_PROP_START_LEARNING_B,
	XM_PROP_STOP_LEARNING_B,
	XM_PROP_SET_LEARNING_POWER_B,
	XM_PROP_GET_LEARNING_POWER_B,
	XM_PROP_GET_LEARNING_POWER_DEV_B,
	/*********nvt fuelgauge feature*********/
	/*fuelgauge test node*/
	XM_PROP_FG1_QMAX,
	XM_PROP_FG1_RM,
	XM_PROP_FG1_FCC,
	XM_PROP_FG1_SOH,
	XM_PROP_FG1_FCC_SOH,
	XM_PROP_FG1_CYCLE,
	XM_PROP_FG1_FAST_CHARGE,
	XM_PROP_FG1_CURRENT_MAX,
	XM_PROP_FG1_VOL_MAX,
	XM_PROP_FG1_TSIM,
	XM_PROP_FG1_CELL1_RASCALE,
	XM_PROP_FG1_AVG_CURRENT,
	XM_PROP_FG1_TAMBIENT,
	XM_PROP_FG1_TREMQ,
	XM_PROP_FG1_TFULLQ,
	XM_PROP_FG1_RSOC,
	XM_PROP_FG1_AI,
	XM_PROP_FG1_CELL1_VOL,
	XM_PROP_FG1_CELL2_VOL,
	/* dual fuelgauge test node only for L18*/
	XM_PROP_SLAVE_CHIP_OK,
	XM_PROP_SLAVE_AUTHENTIC,
	XM_PROP_FG1_VOL,
	XM_PROP_FG1_SOC,
	XM_PROP_FG1_TEMP,
	XM_PROP_FG1_IBATT,
	XM_PROP_FG1_ChargingStatus,
	XM_PROP_FG1_GaugingStatus,
	XM_PROP_FG1_FullChargeFlag,
	XM_PROP_FG2_VOL,
	XM_PROP_FG2_SOC,
	XM_PROP_FG2_TEMP,
	XM_PROP_FG2_IBATT,
	XM_PROP_FG2_QMAX,
	XM_PROP_FG2_RM,
	XM_PROP_FG2_FCC,
	XM_PROP_FG2_SOH,
	XM_PROP_FG2_FCC_SOH,
	XM_PROP_FG2_CYCLE,
	XM_PROP_FG2_FAST_CHARGE,
	XM_PROP_FG2_CURRENT_MAX,
	XM_PROP_FG2_VOL_MAX,
	XM_PROP_FG2_TSIM,
	XM_PROP_FG2_CELL1_RASCALE,
	XM_PROP_FG2_AVG_CURRENT,
	XM_PROP_FG2_TAMBIENT,
	XM_PROP_FG2_TREMQ,
	XM_PROP_FG2_TFULLQ,
	XM_PROP_FG2_ChargingStatus,
	XM_PROP_FG2_GaugingStatus,
	XM_PROP_FG2_FullChargeFlag,
	XM_PROP_FG2_RSOC,
#ifndef CONFIG_MI_CHARGER_M81
	XM_PROP_FG2_OVER_PEAK_FLAG,
	XM_PROP_FG2_CURRENT_DEVIATION,
	XM_PROP_FG2_POWER_DEVIATION,
	XM_PROP_FG2_AVERAGE_CURRENT,
	XM_PROP_FG2_AVERAGE_TEMPERATURE,
	XM_PROP_FG2_START_LEARNING,
	XM_PROP_FG2_STOP_LEARNING,
	XM_PROP_FG2_SET_LEARNING_POWER,
	XM_PROP_FG2_GET_LEARNING_POWER,
	XM_PROP_FG2_GET_LEARNING_POWER_DEV,
	XM_PROP_FG2_GET_LEARNING_TIME_DEV,
	XM_PROP_FG2_SET_CONSTANT_POWER,
	XM_PROP_FG2_GET_REMAINING_TIME,
	XM_PROP_FG2_SET_REFERANCE_POWER,
	XM_PROP_FG2_GET_REFERANCE_CURRENT,
	XM_PROP_FG2_GET_REFERANCE_POWER,
	XM_PROP_FG2_START_LEARNING_B,
	XM_PROP_FG2_STOP_LEARNING_B,
	XM_PROP_FG2_SET_LEARNING_POWER_B,
	XM_PROP_FG2_GET_LEARNING_POWER_B,
	XM_PROP_FG2_GET_LEARNING_POWER_DEV_B,
#endif /* !CONFIG_MI_CHARGER_M81 */
	XM_PROP_FG_VENDOR_ID,
	/*begin dual fuel high temperature intercept feature */
	XM_PROP_FG_VOLTAGE_MAX,
	XM_PROP_FG_Charge_Current_MAX,
	XM_PROP_FG_Discharge_Current_MAX,
	XM_PROP_FG_TEMP_MAX,
	XM_PROP_FG_TEMP_MIN,
	XM_PROP_FG_TIME_HT,
	XM_PROP_FG_TIME_OT,
	XM_PROP_FG_TIME_UT,
	XM_PROP_FG_TIME_LT,
	XM_PROP_FG_SEAL_SET,
	XM_PROP_FG1_SEAL_STATE,
	XM_PROP_FG1_DF_CHECK,
	XM_PROP_FG2_SEAL_STATE,
	XM_PROP_FG2_DF_CHECK,
	/*end dual fuel high temperature intercept feature*/
#if defined(CONFIG_BQ_CLOUD_AUTHENTICATION)
	XM_PROP_SERVER_SN,
	XM_PROP_SERVER_RESULT,
	XM_PROP_ADSP_RESULT,
#endif
#if defined(CONFIG_MI_ENABLE_DP)
	XM_PROP_HAS_DP,
#endif
#if defined(CONFIG_REVERSE_33W)
	XM_PROP_DOWNSHIFT,
	XM_PROP_SNK_PROTOCOL,
	XM_PROP_SCREEN_UNLOCK,
	XM_PROP_REVERSE_THERMAL,
#endif
#ifdef CONFIG_MI_CHARGER_M81
	XM_PROP_ATEST,
#endif /* CONFIG_MI_CHARGER_M81 */
	XM_PROP_LAST_NODE,
	XM_PROP_MAX,
};

enum {
	QTI_POWER_SUPPLY_USB_TYPE_HVDCP = 0x80,
	QTI_POWER_SUPPLY_USB_TYPE_HVDCP_3,
	QTI_POWER_SUPPLY_USB_TYPE_HVDCP_3P5,
	QTI_POWER_SUPPLY_USB_TYPE_USB_FLOAT,
	QTI_POWER_SUPPLY_USB_TYPE_HVDCP_3_CLASSB,
};

struct battery_charger_set_notify_msg {
	struct pmic_glink_hdr	hdr;
	u32			battery_id;
	u32			power_state;
	u32			low_capacity;
	u32			high_capacity;
};

struct battery_charger_notify_msg {
	struct pmic_glink_hdr	hdr;
	u32			notification;
};

struct battery_charger_req_msg {
	struct pmic_glink_hdr	hdr;
	u32			battery_id;
	u32			property_id;
	u32			value;
};

struct battery_charger_resp_msg {
	struct pmic_glink_hdr	hdr;
	u32			property_id;
	u32			value;
	u32			ret_code;
};

struct wls_fw_resp_msg {
	struct pmic_glink_hdr   hdr;
	u32                     property_id;
	u32			value;
	char                    version[MAX_STR_LEN - 32];
};

enum xm_chg_debug_type {
	CHG_WLS_DEBUG,
	CHG_ADSP_LOG,
	CHG_DEBUG_TYPE_MAX,
};

struct chg_debug_msg {
	struct pmic_glink_hdr   hdr;
	u32                     property_id;
	u8                      type;
	char                    data[CHG_DEBUG_DATA_LEN];
};

struct battery_model_resp_msg {
	struct pmic_glink_hdr	hdr;
	u32			property_id;
	char			model[MAX_STR_LEN];
};

struct xm_set_wls_bin_req_msg {
  struct pmic_glink_hdr hdr;
  u32 property_id;
  u16 total_length;
  u8 serial_number;
  u8 fw_area;
  u8 wls_fw_bin[MAX_STR_LEN];
};  /* Message */

struct wireless_fw_check_req {
	struct pmic_glink_hdr	hdr;
	u32			fw_version;
	u32			fw_size;
	u32			fw_crc;
};

struct wireless_fw_check_resp {
	struct pmic_glink_hdr	hdr;
	u32			ret_code;
};

struct wireless_fw_push_buf_req {
	struct pmic_glink_hdr	hdr;
	u8			buf[WLS_FW_BUF_SIZE];
	u32			fw_chunk_id;
};

struct wireless_fw_push_buf_resp {
	struct pmic_glink_hdr	hdr;
	u32			fw_update_status;
};

struct wireless_fw_update_status {
	struct pmic_glink_hdr	hdr;
	u32			fw_update_done;
};

struct wireless_fw_get_version_req {
	struct pmic_glink_hdr	hdr;
};

struct wireless_fw_get_version_resp {
	struct pmic_glink_hdr	hdr;
	u32			fw_version;
};

struct battery_charger_ship_mode_req_msg {
	struct pmic_glink_hdr	hdr;
	u32			ship_mode_type;
};

struct xm_verify_digest_resp_msg {
	struct pmic_glink_hdr	hdr;
	u32			property_id;
	u8			digest[BATTERY_DIGEST_LEN];
	/*dual battery master and slave flag*/
	bool		slave_fg;
};

struct battery_charger_shutdown_req_msg {
	struct pmic_glink_hdr	hdr;
};

struct xm_ss_auth_resp_msg {
	struct pmic_glink_hdr	hdr;
	u32			property_id;
	u32			data[BATTERY_SS_AUTH_DATA_LEN];
};

struct psy_state {
	struct power_supply	*psy;
	char			*model;
	char			*version;
	const int		*map;
	u32			*prop;
	u32			prop_count;
	u32			opcode_get;
	u32			opcode_set;
};

struct battery_chg_dev {
	struct device			*dev;
	struct class			battery_class;
	struct pmic_glink_client	*client;
	struct typec_role_class		*typec_class;
	struct mutex			rw_lock;
	struct rw_semaphore		state_sem;
	struct completion		ack;
	struct completion		fw_buf_ack;
	struct completion		fw_update_ack;
	struct psy_state		psy_list[PSY_TYPE_MAX];
	struct dentry			*debugfs_dir;
	void				*notifier_cookie;
	/* extcon for VBUS/ID notification for USB for micro USB */
	struct extcon_dev		*extcon;
	u32				*thermal_levels;
	const char			*wls_fw_name;
	int				curr_thermal_level;
	int				curr_wlsthermal_level;
	int				num_thermal_levels;
	int				shutdown_volt_mv;
	atomic_t			state;
	struct work_struct		subsys_up_work;
	struct work_struct		usb_type_work;
	struct work_struct		battery_check_work;
	struct work_struct		notify_blankstate_work;
	int				fake_soc;
	bool				block_tx;
	bool				ship_mode_en;
	bool				debug_battery_detected;
	bool				wls_not_supported;
	bool				wls_fw_update_reqd;
	bool				debug_work_en;
	u32				wls_fw_version;
	u16				wls_fw_crc;
	u32				wls_fw_update_time_ms;
	struct notifier_block		reboot_notifier;
	struct notifier_block		shutdown_notifier;
	u32				thermal_fcc_ua;
	u32				restrict_fcc_ua;
	u32				last_fcc_ua;
	u32				usb_icl_ua;
	u32				reverse_chg_flag;
	u32				boost_mode;
	u32				thermal_fcc_step;
	u32				connector_type;
	u32				usb_prev_mode;
	bool				restrict_chg_en;
	struct delayed_work		xm_prop_change_work;
	struct delayed_work		charger_debug_info_print_work;
#if defined(CONFIG_BQ_FG_UPDATE)
	struct delayed_work		batt_update_work;
#endif
	struct delayed_work		panel_notify_register_work;
	struct delayed_work		panel_sec_notify_register_work;
	/* To track the driver initialization status */
	bool				initialized;
	u8				*digest;
	u32				*ss_auth_data;
	char				wls_debug_data[CHG_DEBUG_DATA_LEN];
	/*shutdown delay is supported*/
	bool				shutdown_delay_en;
	bool				support_2s_charging;
	bool				report_power_absent;
	bool				report_connector_temp;
	bool				support_dual_panel;
	/*dual battery authentic flag*/
	bool				slave_fg_verify_flag;

	/*soc update flag*/
	bool				support_soc_update;
	bool				support_screen_update;

	/*battery auth check for ssr*/
	bool				battery_auth;
	bool				slave_battery_auth;
	int				mtbf_current;
	bool				notify_en;
	bool				error_prop;
	struct work_struct pen_notifier_work;
	struct work_struct current_battery_level_notifier_work;
#ifndef CONFIG_MI_CHARGER_M81
	int thermal_board_temp;
	struct notifier_block chg_nb;
#endif /* !#ifndef CONFIG_MI_CHARGER_M81 */
};
