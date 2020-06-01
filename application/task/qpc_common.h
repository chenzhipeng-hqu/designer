/**
 ******************************************************************************
 * @file    xxx.h
 * @author  chenzhipeng
 * @version V1.0.0
 * @date    29-Jun-2019
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/** @addtogroup Project
  * @{
  */

/* Define to prevent recursive inclusion */
#ifndef __QPC_COMMON_H__
#define __QPC_COMMON_H__

#ifdef __cplusplus
 extern "C" {
#endif

/***********************************************
                    include
***********************************************/
#include <third/qpc/include/qpc.h>
#ifdef Q_SPY
	#include <third/qpc/include/qs.h>
#endif

/***********************************************
                    define
***********************************************/
#define     TICKS_PER_SEC       	100

#define     QPC_SIG_ENUM_CASE(x)  case x: return(#x)

#define     BUFF_LEN_MAX					128

/***********************************************
                    typedef
***********************************************/
 enum QPCSignals {
 	Q_EMPTY_SIG = 0,
 	TIME_TICK_SIG = Q_USER_SIG,
 	TERMINAL_SIG,
    RESULT_SIG,
 	MAX_PUB_SIG,                /* the last published signal */

 	TEST_TIMEOUT_SIG,
	REBACK_SIG,
 	DEBUG_LEVEL_SIG,
    SEND_ERR_SIG,
    TIMEOUT_SIG,

	/* debug */
	LOG_WRITE_SIG,
	LOG_WRITE_OK_SIG,
	LOG_WRITE_ERR_SIG,

	/* boardx */
	GET_BOARD_STATUS_SIG,
    CLIENT_EXTERNAL_START_SIG,
    CLIENT_START_SIG,
    EXTERNAL_START_SIG,
    READY_TIMEOUT_SIG,
    READ_IO_TIMEOUT_SIG,
	POWEROFF_TIMEOUT_SIG,
	BOARD_READY_SIG,
	BOARD_UPLIFT_SIG,
	BOARD_PASS_SIG,
	BOARD_NG_SIG,
	BOARD_RESET_SIG,
	BOARD_RESULT_RESET_SIG,
	BOARD_SELF_SIG,
	BOARD_BLON_SIG,
	BOARD_PSON_SIG,
	BOARD_ADJ_SIG,
	BOARD_SHORT_V12_SIG,
	BOARD_V12_SW_SIG,
	BOARD_POWEROFF_SIG,
	BOARD_ENTER_AGING_SIG,
	BOARD_AGING_STA_SIG,
	GPIO_OUTPUT_SIG,
	GPIO_INPUT_SIG,

	/* V220 */
	PCT_220V_ON_SIG,
	PCT_220V_OFF_SIG,
	PCT_220V_P_ON_SIG,
	PCT_220V_N_ON_SIG,
	PCT_220V_P_OFF_SIG,
	PCT_220V_N_OFF_SIG,
	PCT_CAP_SIG,
	GET_CAP_CONNECT_SIG,
	CAP_TIMEOUT_SIG,
	PCT_AMP_SIG,
	PHASE_DET_SIG,
	RELAY_P_TIMEOUT_SIG,
	RELAY_N_TIMEOUT_SIG,
	START_RELAY_TIMER_SIG,
	START_POWEROFF_TIMER_SIG,
	KEY_TIMEOUT_SIG,

	/* PWM */
	PWM_BOARD_SIG,
	PWM_LOGIC_SIG,
	SET_PWM_FREQ_SIG,
	SET_PWM_DUTY_SIG,
	SET_LOGIC_PWM_INTERVAL,

	/* adc */
	GET_ADC_VALUE_SIG,
	GET_CH_VOL_SIG,
	CALC_VOL_TIMEOUT_SIG,

	/* atsx */
	GET_ATSX_POW_SIG,
	ATSX_POW_TIMEOUT_SIG,
	ATSX_POW_PRINT_ON_SIG,
	ATSX_POW_PRINT_OFF_SIG,

	/* can */
	ATSX_CAN_TIMEOUT_SIG,

	/* ethernetif */
	SET_LINK_TIMEOUT_SIG,
	LWIP_RX_READY_SIG,
	LINK_UP_SIG,
	LINK_DOWN_SIG,
	DHCP_TIMEOUT_SIG,
	SET_IP_SIG,
	GET_IP_SIG,
	SET_MAC_SIG,
	GET_MAC_SIG,

	/* socket */
	SOCKET_RX_TIMEOUT_SIG,
	SOCK_ACCEPT_TIMEOUT_SIG,
	SOCK_TX_SIG,
	SOCK_DIS_CONNECT_SIG,
	SOCKET_DISPATCH_TIMEOUT_SIG,
	SOCK_CONNECT_SIG,
	SOCK_RX_TIMEOUT_SIG,
	SOCK_HEART_HEAT_SIG,
	SOCK_HEART_HEAT_TIMEOUT_SIG,

	/* test ctrl */
    GET_CONF_SIG,
    READ_CONF_SIG,
    ONCE_CONF_SIG,
    GET_TEST_SIG,
    ONCE_TEST_SIG,
    READ_TEST_SIG,
    GET_CMD_SIG,
    ONCE_CMD_SIG,
    READ_CMD_SIG,
    STATUS_SIG,
    PROGRESS_SIG,
    ERROR_SIG,
    READ_SIG,
    FETCH_SIG,
    STOP_SIG,
    START_SIG,
    TEST_INTERVAL_TIMEOUT_SIG,
    PRINT_JSON_CONF_SIG,
    PRINT_JSON_TEST_SIG,
    PRINT_JSON_CMD_SIG,

	/* 485, 232  */ 
	SEND_TIMEOUT_SIG,
	SEND_SIG,
	RECEIVE_OK_SIG,
	RECEIVE_DATA_SIG,
	READ_HOLD_REG_SIG,
	WRITE_SIGNAL_HOLD_REG_SIG,
	WRITE_MULTI_HOLD_REG_SIG,
	READ_INPUT_REG_SIG,
	SEND_OK_SIG,
	SET_BAUDRATE_SIG,
    V220_TIMEOUT_SIG,

 	MAX_SIG                     /* the last signal */
 };

typedef enum{
	BOARD_A,
	BOARD_B,
	BOARD_MAX
}BOARDx;

typedef enum{
	RS485_IN,
	RS485_EX,
	RS485_MAX
}RS485x;

typedef enum
{
	NONE,
	PM_ADDR_A				= 0x01,
	LEDLOAD_ADDR_A,
	ELOAD_ADDR_A,
	PM_ADDR_B				= PM_ADDR_A | (BOARD_B << 4),
	LEDLOAD_ADDR_B,
	ELOAD_ADDR_B,
	MODBUS_ADDR_MAX
}MODBUS_ADDRx;

#ifdef Q_SPY
//    enum AppRecords { /* application-specific trace records */
//        TEST_STAT = QS_USER,
//		TEST_STAT2,
//        COMMAND_STAT
//    };

#endif

typedef enum  // the same as upper computer, follow commane list
{
	V5_1,
	V5_2,
	V5_3,
	V12,
	VAMP,			// power amplifier
	V1215_P,
	V1215_N,
	VIMP_TEST,   	//Impedance test interface
	BOARD_ADC_CH_MAX
}BOARD_ADC_CH;

typedef enum
{
	BOARD_PWM,
	LOGIC_PWM1,
	LOGIC_PWM2,
	LOGIC_PWM3,
	LOGIC_PWM4,
	PWM_NUM_MAX
}BOARD_PWM_CH;

 typedef struct {
 	QEvt 		super;
 	uint8_t 	u8Param1;
 	uint8_t 	u8Param2;
 	uint8_t 	u8Param3;
 	uint8_t 	u8Param4;
 }DebugLevelEvt, TestProgressEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	BOARD_ADC_CH get_adc_chx;
 	unsigned short int ch_vol;
 }AdcEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	BOARD_PWM_CH pwm_num;
 	unsigned short int duty;  //0~999
 	unsigned int freq;  			//855HZ ~ 1MHz  3��Ƶ
 	unsigned int logicInterval;

 }PwmEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	unsigned char 	socket_n;
 }AtsxEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	unsigned char 	socket_n;
 	uint16_t times;
 }LedRedEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	unsigned char pinState;
 	uint8_t					pinId;
 }GpioEvt;

 typedef struct {
 	QEvt super;
 	QActive const * sender;
 	unsigned short int 	cmd_id;
 	unsigned short int timeout;
 	unsigned short int eload_chx;
 }ScpEvt, PowerOffEvt;  // short circuit

 typedef struct {
 	QEvt 					super;
 	unsigned char rlyP_time;
 	unsigned char rlyN_time;
 	unsigned int tick;
 }RlyTimerEvt, PowTimerEvt;

typedef struct {
    QEvt        super;
    uint32_t baudrate;
}UartEvt;

typedef struct {
    QEvt        super;
    void        *json;
    uint32_t    len;
}JsonPointEvt;

typedef struct {
    QEvt                    super;
    QActive const * sender;
    unsigned short int  cmd_id;
    unsigned char   socket_n;
    unsigned char addr[4];
}IpEvt;

typedef struct {
    QEvt                    super;
    QActive const * sender;
    unsigned short int  cmd_id;
    unsigned char   socket_n;
    unsigned char addr[6];
}MacEvt;

typedef struct {/* protected: */
    QEvt super;
    int len;
    unsigned char socket_n;
    char write_buff[BUFF_LEN_MAX];
} RS485SendEvt, RS232SendEvt, ProtocolSendEvt, ErrorMsgEvt;

typedef struct {
	QEvt super;
	QActive const * sender;
	unsigned short int 	cmd_id;
	unsigned char 	socket_n;
	uint16_t start_addr;
	uint16_t reg_count;
	uint16_t slave_addr;
	uint16_t reg_value;
	
}ModbusEvt;

/***********************************************
               function prototypes
***********************************************/
 extern void Test_Ctor(uint8_t _prio);
 extern void Board_Ctor(uint8_t _prio);
 extern void Board_Ctor(uint8_t _prio);
 extern void RS485_Ctor(uint8_t _prio, RS485x rs485x);
 extern void Ethernet_Ctor(uint8_t _prio);
 extern void TestCtrl_Ctor(uint8_t _prio, BOARDx boardx);
 extern void TestCmd_Ctor(uint8_t _prio, BOARDx boardx);

 extern QHsm * BoardV220_Ctor(uint8_t _id);
 extern QHsm * BoardAdc_Ctor(uint8_t _id);
 extern QHsm * BoardGpio_Ctor(uint8_t _id);
 extern QHsm * BoardPwm_Ctor(uint8_t _id);
 extern QHsm * RS485Modbus_Ctor(uint8_t _id);

//uint8_t *TestCtrl_MergeConf(void);
//uint8_t *TestCtrl_MergeTest(void);
//uint8_t *TestCmd_MergeCmd(void);

extern uint8_t *TestCtrl_GetConf(void);
extern uint8_t *TestCtrl_GetTest(void);
extern uint8_t *TestCmd_GetCmd(void);

/***********************************************
	      		    inline
***********************************************/
const char *QPC_SIG_TO_STRING(QSignal sig_);

/***********************************************
                   variable
***********************************************/
 extern QActive * const AO_Test;
 extern QActive * const AO_Ethernet;
 extern QActive * const AO_Board[];
 extern QActive * const AO_RS485[];
 extern QActive * const AO_TestCtrl[];
 extern QActive * const AO_TestCmd[];

#ifdef __cplusplus
}
#endif

#endif /* __QPC_COMMON_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/


