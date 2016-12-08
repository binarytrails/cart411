var serialport = require("serialport")
var SerialPort = serialport.SerialPort;
var fs = require('fs');
var sys = require('sys');
var exec = require('child_process').exec;

const NMLED = 30;

var tm = null;

var pdfs = [];

//get all pdfs names
pdfs = fs.readdirSync('./files/');

//open serialPort
var serialPort = new SerialPort("/dev/ttyUSB0", {
  parser: serialport.parsers.readline("\n"), //readline parser
  baudrate: 9600
});


serialPort.open(function (error) {
  if ( error ) {
    console.log('failed to open: '+error);
  } else {
    console.log('open');

    serialPort.on('data', function(data) {
      //whenever we receive a value, clear the timeout
      clearTimeout(tm);

      //get the right pdf according to the slider position
      var mapped = mod(map(Number(data), 0, NMLED, 0, pdfs.length), pdfs.length);

      //print in 2 secs if no new value
      tm = setTimeout((function(){
        print(this.filename);
      }).bind({filename : pdfs[mapped]}), 2000) //use bind to keep the value, regardless of context
    });

  }
});


function print(filename){
  //print using lpr
  exec("lpr -o fit-to-page files/" + filename);
}


//mathematical modulo
function mod(a, b)
{
  var r = a % b;
  return Math.floor(r < 0 ? r + b : r);
}


function map(x,  in_min,  in_max,  out_min,  out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
