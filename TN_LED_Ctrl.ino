
/*
TN的红外感应器触发动态led灯带和播放视频
接收："video_stop"，"video_play"
发送："play"，"stop"
功能：没触摸时视频时待机界面，当触发红外感应器时启动动态灯带和播放视频，播放视频当中被触摸
     不会执行，播放视频结束后回到待机界面
问题：arduino的启动加载会有一个检测后再加载的过程，所以不能开机后就发指令
 */
 
#include <SoftwareSerial.h> 

#define LEDWallPinRx 8  //墙面LED模块接收端
#define LEDWallPinTx 7  //墙面LED模块发射端

int Sensor = 10;  //定义触发红外感应器模块接收端的针脚为10

String cmd = "stop" ;
String VedioState = "video_stop";

//LED 模块软连接
SoftwareSerial LEDWallModel(LEDWallPinRx, LEDWallPinTx); // RX, TX

//播放LED跑动命令
byte playLED[] = {0xAA,0x26};

//停止播放LED跑动命令
byte stopLED[] = {0xAA,0x62};

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  LEDWallModel.begin(9600);
  pinMode(Sensor,INPUT);
}

void loop() {

  // 读取触发针脚的状态
  int buttonState ;
  String VedioTempState = "";

  // 读取上位机播放视频的状态
  if(Serial.available() > 0)
  {
    while (Serial.available() > 0) 
    {
      VedioTempState += char(Serial.read());
      delay(2);
    }
    VedioState = VedioTempState;
  }
  //Serial.println("vedio:"+VedioState+" ");
  
  // 判断上位机是否在播放视频，如果播放视频就让视频播完
  // 如果没有播放视频，有触发感应器就发送播放视频指令，没触发就发送停止视频指令
  if(VedioState == "video_stop")
  {
    buttonState = digitalRead(Sensor);
    if((buttonState == HIGH)&&(cmd == "stop")) //被触发后发播放命令，不会重复发送
    {
      cmd = "play";
      LEDWallModel.write(playLED,2);
      Serial.println(cmd);
    }
      
   if((buttonState == LOW)&&(cmd == "play"))  //没有触发后发停止命令，不会重复发送
   {
      cmd = "stop";
      LEDWallModel.write(stopLED,2);
      Serial.println(cmd);
   }
      
    //Serial.println((String)i+" oldcmd:"+oldcmd+" cmd:"+cmd);
  }

  delay(50);        // delay in between reads for stability

}

