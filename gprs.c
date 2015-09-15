/**
* O2EE GPRS Debug Source 0.0.1
* Copyright ©2000-2009 O2ee Enterprises Ltd. All Rights Reserved.
* This file may not be redistributed in whole or significant part.
* http://www.o2ee.com | http://www.o2ee.com/license.html
*/

char *AT_Command[12] = {
	"at\r\n",		/*判断是否连线 */
    "at+csq\r\n",		/**判断信号质量*/
	"at+creg?\r\n",		//检查模块网络注册情况
	"at+wopen=1\r\n",	//打开OPEN AT协议
	"AT+WIPCFG=1\r\n",	//启动TCP协议
	"AT+WIPBR=1,6\r\n",	//打开GPRS
	"at+wipbr=2,6,11,\"CMNET\"\r\n",	//设置GPRS APN名称
	"AT+WIPBR=4,6,0\r\n",	//启动GPRS客户端
    "at+wipcreate=2,1,\"192.168.2.1\",8763\r\n",	//设置IP和端口号
	"at+wipdata=2,1,1\r\n",	//连接
	"+++\r\n",		//返回AT命令状态
	"AT+WIPCLOSE=2,1\r\n"	//关闭连接
};

char chEchoData[20] = { 0 };

//------------------------------------------------------
// function : send command
// input    : AT instruction
// output   : none
// description: send AT instruction wait for echo if succeed
//------------------------------------------------------

void GPRS_Cmd(char *pt)
{
	int i = 0;
	while (1) {
		if (pt[i] != '\0') {
			Uart_SendByte(pt[i]);
			i++;
		}
		else {
            //      Uart_GetString(chEchoData);
			break;
		}
	}
}

//------------------------------------------------------
// function : GPRS initialize
// input    : none
// output   : none
// description: send AT instruction initialize GPRS communition
//------------------------------------------------------

void GPRS_Init(void)
{

	Uart_Select(0);		//选择串口0
	Uart_Init(0, 9600);	//9600N81
	Delay(5000);
 GPRS_START:			//为了方便调试指令,没有使用循环语句
	GPRS_Cmd(AT_Command[0]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[1]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[2]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[3]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[4]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[5]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[6]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[7]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[8]);
	//      if(memcmp(chEchoData,"OK",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
	GPRS_Cmd(AT_Command[9]);
	//      if(memcmp(chEchoData,"CONNECT",2) != 0)
	//              goto GPRS_START;
	Delay(5000);
}

//------------------------------------------------------
// function : return AT command mode
// input    : none
// output   : none
// description: return AT mode ,you can input AT command
//------------------------------------------------------

void GPRS_ReturnAT(void)
{
    GPRS_Cmd(AT_Command[10]); //send +++
	Delay(5000);
}

//------------------------------------------------------
// function : GPRS communition close
// input    : none
// output   : none
// description: close tcp link
//------------------------------------------------------

void GPRS_Close(void)
{
 GPRS_START:
	GPRS_Cmd(AT_Command[11]);
	if (memcmp(chEchoData, "OK", 2) != 0)
		goto GPRS_START;
	Delay(5000);
}

//------------------------------------------------------
// function : send data
// input    : string data
// output   : none
// description: send data to server
//-----------------------------------------------------

void GPRS_SendData(char *pd)
{
	//      GPRS_Init();
	Uart_SendString(pd);
	Uart_SendByte(0x1A);	//ctrl+z   26
	Delay(5000);
}
