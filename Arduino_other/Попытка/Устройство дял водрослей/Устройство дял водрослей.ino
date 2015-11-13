#define Led_Pin 5 // пока что установим 5 пин
#define Button_Pin  8 // пин кнопки

#define STATE_SHINE  0 // Always Shine
#define STATE_BLINK  1 // NOW IT BLINK
#define STATE_FADE   2 // потухает и начинает медленно светить 

#define BLINK_DELAY 2000 // часота мигания
 
#define FADA_TIME 10000 // время потухания
#define FASE_STEP_DELAY // частота потухания 

int ledState = STATE_SHINE; // состояние светодиодов
bool wasButtonDown = false; // была ли нажата кнопка

void setup()
{
	pinMode(Led_Pin,OUTPUT);
	pinMode(Button_Pin,INPUT);
}

void loop()
{
	bool isButtonDown = digitalRead(Button_Pin); // нажата кнопка сейчас
	if(isButtonDown && !wasButtonDown){
		if (ledState == STATE_SHINE)
			ledState = STATE_BLINK;
		else if (ledState == STATE_BLINK)
			ledState = STATE_FADE;
		else
			ledState = STATE_SHINE;
		delay(10);
	}
	wasButtonDown = isButtonDown;
	switch(ledState){
		case STATE_SHINE:
			digitalWrite(Led_Pin, HIGH);
			break;
		case STATE_BLINK:
			digitalWrite(Led_Pin,(milis() / BLINK_DELAY) % 2);
			break;
		case STATE_FADE:
			digitalWrite(Led_Pin,(milis() / FASE_STEP_DELAY) % 256);
			break;
	}
}

