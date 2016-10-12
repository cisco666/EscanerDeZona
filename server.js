
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port=5000;

app.get('/',function(req,res)
{
	res.sendFile(__dirname + '/index.html')
});

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

var portS="COM5";

var sp = new SerialPort(portS, {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
},false);
sp.open(function (error) 
{
  	if ( error ) 
  	{
    	console.log('Failed to open port: '+portS+" "+error);
    } 
    else 
    {
    	console.log('Serial Port Opend');
		io.sockets.on('connection', function(socket)
		{
		    console.log(' - A User Connected !!!');

		    socket.on('start',function(msg)
		    {
		    	sp.write(msg,function()
		    	{
		    		console.log("Start: " + msg);
		    	});
		    });
	    	sp.on('data', function(dato)
		    {
		    	var receivedData = dato.toString();
			  	var data1=receivedData.split(':');
			  	console.log(receivedData+'\n'+data1[1]+' '+data1[2]+' '+data1[3]+' '+data1[4]+'\n');
			  	socket.emit('data', receivedData);

		    });	
  		});
    }
});



http.listen(port, function()
{
  console.log('Listening on port :'+port);
});
