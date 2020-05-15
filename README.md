# remote_manage
用于运行在imx6ull平台的远程管理方案  
初步规划的功能:  
1.利用串口控制嵌入式平台的设备和读取内部状态信息  
2.支持socket通讯管理  
3.支持远程web访问  
  
计划项目结构  
document/   文档说明(仅简单说明，设计思路参考下面链接)  
kernal_mod/ 内核驱动模块说明或者实现  
lower_app/  下位机代码实现  
test/       测试代码  
upper_app/  上位机代码实现  

相关的设计资料说明参考  
https://www.cnblogs.com/zc110747/p/12747213.html    

硬件适配:  
下位机驱动适配平台(kernal_mod):正点原子I.MX6U-ALPHA 开发板  
下位机应用层适配平台(lower_app):兼容嵌入式Linux平台，仅修改设备文件名即可支持  
上位机兼容性(upper_app):仅测试window10平台， 不保证其它本版本系统的兼容性      

编译环境  
下位机交叉编译工具:arm-linux-gnueabihf-g++  
上位机编译工具:QT5.12.8  
目前Makefile中路径位绝对路径，实际编译需要修改。  

本项目是我学习嵌入式Linux开发中的实现代码，更详细的资料参考上述链接说明    
另外有问题可直接提交issuses,我会尽快处理。
