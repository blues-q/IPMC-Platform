# IPMC测控平台-NUAA-IBSS

版本索取API：https://api.github.com/repos/drinow/IPMC-Platform/releases/latest

## 更新日志
- 20180709更新
	- 增加了双通道同时控制的支持；
- 20180609更新
	- 硬件上提高了力传感器放大倍数；
	- 增加了过流状态下（1A）的LED指示；
	- 降低了ADC采样速度，以提高检测精度；
- 20180526更新
	- 提高了图表缓冲区大小，新增图表开关，新增采样时间选项，解决长时间运行后程序卡顿问题；
	- 增加温湿度传感器，及其解析；
- 20180525更新
	- 修改上位机协议解析函数，提高了解析准确度；
- 20180519更新
	- 上位机支持波形显示等相关功能；
- 20180518更新
	- 新增简单的ADC归零程序，电压完成校准；
	- 新增自定义ftoa函数，格式化输出；
	- 调整上位机显示界面，增加版本号显示（“关于”按钮）；
	- 上位机新增快捷键支持；
- 20180516更新
	- 新增激光位移传感器检测；
	- 新增错误码指示，LED快闪表示出现错误；
- 20180511更新
	- 上位机增加自动获取管理员权限功能；
	- 修正了多次安装后在应用程序删除列表下可能出现的多个应用的问题；
- 20180506更新
	- 上位机支持自动更新；
- 20180505更新
	- 移植UCOS-II，无操作系统的版本暂不更新；
	- 支持检测版本更新，但尚不支持进行版本更新；
- 20180501更新
	- 新添了自动搜寻串口功能；
	- 细节优化；
- 20180430更新
	- 调通了CAN总线；
	- 增加了上位机；
	- 支持通过CAN总线完成两个板子的级联控制，通过KEY按钮切换板子编号（红、蓝灯）；
	- 标注了原理图缺陷之处；
- 20180312更新
	- 发布第一代PCB；
	- 添加README；
	- 等待PCB测试...；
- 20180407更新
	- 注释了PCB的缺陷之处；
	- 调通DAC和ADC；