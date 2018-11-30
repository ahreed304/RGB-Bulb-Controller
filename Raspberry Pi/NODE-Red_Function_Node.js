//This code receives voice commands from Amazon Alexa, interprests those commands, and outputs them to an Arduino via the USB serial port
//It runs inside of Node-Red, an application installed on my Raspberry Pi.
//This code works with the Alexa-Home node.  It is temporary.  Better code will be written when better nodes become available

var address = msg.topic;
var command = '0';

switch(msg.payload) {
	case     1: command = 'a'; break;
	case     2: command = 'b'; break;
	case     3: command = 'c'; break;
	case     4: command = 'd'; break;
	case     5: command = 'e'; break;
	
	case    25: command = 'W'; break;
	case    50: command = 'X'; break;
	case    75: command = 'Y'; break;
	case   100: command = 'Z'; break;
	case  true: command = 'P'; break;
	case false: command = 'Q'; break;
}

switch(msg.payload.hue) {
    case   0: if(msg.payload.saturation === 0) {command = 'A';}
              else {command = 'B';}	 break;
    case  39: command = 'C'; break;
	case  50: command = 'D'; break;
	case  60: command = 'E'; break;
	case 120: command = 'F'; break;
	case 174: command = 'G'; break;
	case 180: command = 'H'; break;
	case 240: command = 'I'; break;
	case 277: command = 'J'; break;
	case 300: command = 'K'; break;
	case 348: if(msg.payload.saturation == .9087) {command = 'U';}
              else {command = 'L';}	 break;
	case 255: command = 'T'; break;
	case 348: command = 'U'; break;
	case 274: command = 'V'; break;
}

if(address=="0000.0000.0100" || address=="0000.0000.0010") {
	switch(msg.payload) {
		case true:
		case false: command = 'a'; break;
		case   1: command = 'b'; break; 
		case -25:
		case   2: command = 'c'; break;
		case   3: command = 'd'; break;
		case  11: command = 'e'; break; 
		case  25:
		case  12: command = 'f'; break;
		case  13: command = 'g'; break;
		case   0: command = 'h'; break;
		case  91: command = 'i'; break;
		case  92: command = 'j'; break;
		case  93: command = 'k'; break;
	}
}

msg.payload = address.replace(/1/g, command);
return msg;