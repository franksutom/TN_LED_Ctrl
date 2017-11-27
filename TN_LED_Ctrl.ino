
#include <SoftwareSerial.h> 

#define LEDWallPinRx 8  //墙面LED模块接收端
#define LEDWallPinTx 7  //墙面LED模块发射端

#define Sensor 10  //红外LED模块发射端

#define TimeoutMax 300000 //超时时间

//mp3 模块软连接
SoftwareSerial CinemaDoorModel(CinemaDoorPinRx, CinemaDoorPinTx); // RX, TX
SoftwareSerial LEDWallModel(LEDWallPinRx, LEDWallPinTx); // RX, TX
SoftwareSerial LEDGroundModel(LEDGroundPinRx, LEDGroundPinTx); // RX, TX

//影院入口门开命令
byte CinemaEnterOpen[] = {0xFD,0x03,0xEB,0xDD,0x72,0x6C,0xDF};

//影院入口门关命令
byte CinemaEnterClose[] = {0xFD,0x03,0xEB,0xDD,0x78,0x6B,0xDF};

//影院入口门感应开关命令
byte CinemaEnterAuto[] = {0xFD,0x03,0xEB,0xDD,0x71,0x6D,0xDF};

//影院出口门开命令
byte CinemaExitOpen[] = {0xFD,0x03,0x0F,0x55,0x72,0x6D,0xDF};

//影院出口门关命令
byte CinemaExitClose[] = {0xFD,0x03,0x0F,0x55,0x71,0x6D,0xDF};

//影院出口门感应开关命令
byte CinemaExitAuto[] = {0xFD,0x03,0x0F,0x55,0x78,0x6D,0xDF};

//播放LED跑动命令
byte playLED[] = {0xAA,0x26};

//停止播放LED跑动命令
byte stopLED[] = {0xAA,0x62};

//设置状态
boolean onFlag=false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  CinemaDoorModel.begin(9600);
  LEDWallModel.begin(9600);
  LEDGroundModel.begin(9600);
}

void loop() {

  String cmd = readCmd();

  Serial.print(cmd);

  if(cmd.startsWith("Run"))
  {
    LEDWallModel.write(playLED,2);
    delay(3000);
    LEDGroundModel.write(playLED,2);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("Stop"))
  {
    LEDWallModel.write(stopLED,2);
    delay(50);
    LEDGroundModel.write(stopLED,2);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("OpenEnterDoor"))
  {
    LEDWallModel.write(CinemaEnterOpen,7);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("CloseEnterDoor"))
  {
    LEDWallModel.write(CinemaEnterClose,7);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("AutoEnterDoor"))
  {
    LEDWallModel.write(CinemaEnterAuto,7);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("OpenExitDoor"))
  {
    LEDWallModel.write(CinemaExitOpen,7);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("CloseExitDoor"))
  {
    LEDWallModel.write(CinemaExitClose,7);
    onFlag= true;
    Serial.println(" ok");
  }
  else if(cmd.startsWith("AutoExitDoor"))
  {
    LEDWallModel.write(CinemaExitAuto,7);
    onFlag= true;
    Serial.println(" ok");
  }
 
  delay(50);
}

//读取指令操作
String readCmd(){
   boolean stringComplete=false;
   String inputString="";
   //Serial.listen();
    delay(50);
   while(Serial.available()>0 && stringComplete==false){
          char inChar = (char)Serial.read();
          if (inChar == '\n') {
              stringComplete = true;
          }else{
              inputString += inChar;               
          }
    }
    return inputString;
}

