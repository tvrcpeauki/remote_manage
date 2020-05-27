# remote_manage

SPI驱动的实现包含三部分
1.设备树的添加，修改
注:设备树文件为kernal/dts/imx6ull-14x14-evk.dts
添加设备树与SPI3相关的引脚说明到iomuxc/imx6ul-evk下
pinctrl_ecspi3: ecspi3grp {
        fsl,pins = <
                MX6UL_PAD_UART2_RTS_B__ECSPI3_MISO        0x100b1  /* MISO*/
                MX6UL_PAD_UART2_CTS_B__ECSPI3_MOSI        0x100b1  /* MOSI*/
                MX6UL_PAD_UART2_RX_DATA__ECSPI3_SCLK      0x100b1  /* CLK*/
                MX6UL_PAD_UART2_TX_DATA__GPIO1_IO20       0x100b0  /* CS*/
        >;
};  
在最外面添加或者完善节点ecspi3
&ecspi3 {
        fsl,spi-num-chipselects = <1>;
        cs-gpio = <&gpio1 20 GPIO_ACTIVE_LOW>;
        pinctrl-names = "default";
        pinctrl-0 = <&pinctrl_ecspi3>;
        status = "okay";

	spidev: icm20608@0 {
	compatible = "alientek,icm20608";
        spi-max-frequency = <8000000>;
        reg = <0>;
    };
};
重新编译设备树，即完成了设备树的修改。

