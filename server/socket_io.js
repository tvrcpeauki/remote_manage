// 1 引入模块
const net = require('net');

// 3 链接
var client = net.connect({port:8000, host:"192.168.1.108"}, function(){
    this.setEncoding('utf8');
    this.setTimeout(500);
    this.on('data',(data)=>{
        console.log(Buffer.from(data).toString("hex"));
    })
    this.on('error',(e)=>{
        console.log(e.message);
    });

    this.on('close',()=>{
        console.log("Socket Close\n");
    });
});

const led_cmd = [0x5a, 0x01, 0x32, 0x23, 
                0x00, 0x08, 0x02, 0x00, 
                0x00, 0x00, 0x03, 0x03, 
                0x00, 0x00, 0xFF, 0xFF];
const buf1 = Buffer.from(led_cmd);
client.write(buf1);