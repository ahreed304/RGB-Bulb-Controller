//This code receives voice commands from Amazon Alexa, interprests those commands, and outputs them to an Arduino via the USB serial port
//It runs inside of Node-Red, an application installed on my Raspberry Pi.
//This code works with the Alexa-Home node.  It is temporary.  Better code will be written when better nodes become available

var address = msg.topic;
// var command = '0';
var command = '';


switch(msg.payload) {
	// not sure what this is
	// case     1: command = 'a'; break;
	// case     2: command = 'b'; break;
	// case     3: command = 'c'; break;
	// case     4: command = 'd'; break;
	// case     5: command = 'e'; break;
	
	case    25: command = 'brightness25'; break;
	case    50: command = 'brightness50'; break;
	case    75: command = 'brightness75'; break;
	case   100: command = 'brightness100'; break;
	case  true: command = 'powerOn'; break;
	case false: command = 'powerOff'; break;
}

switch(msg.payload.hue) {
    case   0: if(msg.payload.saturation === 0) {command = 'white';}
              else {command = 'red';}	 break;
    case  39: command = 'orange'; break;
	case  50: command = 'gold'; break;
	case  60: command = 'yellow'; break;
	case 120: command = 'green'; break;
	case 174: command = 'turquoise'; break;
	case 180: command = 'cyan'; break;
	case 240: command = 'blue'; break;
	case 277: command = 'purple'; break;
	case 300: command = 'magenta'; break;
	case 348: if(msg.payload.saturation == .9087) {command = 'smooth(crimson)';}
              else {command = 'pink';}	 break;
	case 255: command = 'flash(lavender)'; break;
	case 348: command = 'smooth(crimson)'; break;
	case 274: command = 'indigo(speed)'; break;
}
//TV controls
// if(address=="0000.0000.0100" || address=="0000.0000.0010") {
// 	switch(msg.payload) {
// 		case true:
// 		case false: command = 'a'; break;
// 		case   1: command = 'b'; break; 
// 		case -25:
// 		case   2: command = 'c'; break;
// 		case   3: command = 'd'; break;
// 		case  11: command = 'e'; break; 
// 		case  25:
// 		case  12: command = 'f'; break;
// 		case  13: command = 'g'; break;
// 		case   0: command = 'h'; break;
// 		case  91: command = 'i'; break;
// 		case  92: command = 'j'; break;
// 		case  93: command = 'k'; break;
// 	}
// }

// msg.payload = address.replace(/1/g, command);
switch(address) {
    case 'all': address = ["192.168.1.200", "192.168.1.201", "192.168.1.202"]; break;
    // case 'bedroom': address = ["192.168.1.202"]; break;
    // case 'living room': address = ["192.168.1.200", "192.168.1.201"]; break;
}

msg.address = address;
msg.command = command;
// msg.url = ipAddress + "/" + command;
return msg;