IoT technologies:
1. OS: linux, ROS, TCPIP protocol stack
2. Commonication: 4G/5G, LoRaWAN, Bluetooth Mesh, WiFi
3. Power Supply
4. BSP/Driver
5. HW design
6. Firmware update
7. Debugging, JTAG, Cross Compiling, CMake
8. Restful(and authentication), backend database
9. Sensors and interfaces (GNSS, etc.)
10. MQTT

LoRaWAN + ChirpStack(可docker部署):
LoRa 设备 → LoRaWAN 无线 → LoRa 网关 → Gateway Bridge → MQTT → Network Server → Application Server → MQTT/HTTP → 云平台/业务系统

LoRa 设备：只运行 LoRaWAN 协议，通过 LoRa 无线发送数据到网关。
LoRa 网关：接收 LoRa 数据，通过 packet forwarder 发送到 Gateway Bridge。
Gateway Bridge：将 LoRa 数据封装为 MQTT 或 HTTP 消息，转发给 Network Server。
Network Server：处理 LoRaWAN 协议，将应用层数据交给 Application Server。
Application Server：通过 MQTT/HTTP/InfluxDB 等集成，将数据转发到云平台或业务系统

ThingsBoard
ThingsBoard是一个开源的物联网（IoT）平台，用于设备管理、数据收集、处理和可视化。它支持多种协议（如MQTT、CoAP、HTTP），可以快速接入传感器、设备等，并提供规则引擎、告警、仪表盘等功能，帮助用户构建端到端的IoT解决方案。
核心功能：
设备管理：支持设备注册、分组、配置和远程控制。
数据采集：通过MQTT、HTTP等协议接收设备数据，支持遥测和属性数据。
规则引擎：基于事件和条件触发动作，如数据转发、告警、设备控制等。
可视化仪表盘：拖拽式界面，可创建图表、地图、控件等，实时展示设备状态和数据。
告警与通知：支持阈值告警，可通过邮件、短信、Slack等通知用户。
多租户支持：可为不同客户或组织提供独立的工作空间和权限控制。
典型应用场景：工业物联网、智能家居、智慧城市、资产跟踪等，适合需要大规模设备接入和实时监控的项目

海上物联网平台的方案，使用LoRa + NBIOT，传感器有gps，温度和风速传感器，物联网的规模为100个LoRa节点

LoRa终端 → LoRaWAN网关 → ChirpStack → MQTT → ThingsBoard：
    终端通过LoRaWAN协议上报数据（JSON格式：{"lat":xx,"lng":xx,"temp":xx,"wind":xx}）。
    网关通过MQTT/HTTP将数据转发至ThingsBoard。
NB-IoT终端 → ThingsBoard：
    终端通过NB-IoT模块直接连接ThingsBoard MQTT/HTTP接口，上报关键数据。
ThingsBoard → 应用系统：
    通过REST API/RPC将数据推送给业务系统（如船舶管理系统、气象预警平台）。


终端节点设计（100节点）
1. 硬件架构
主控：STM32系列MCU（如STM32L0/L4），低功耗设计，支持LoRaWAN协议栈。
通信模块：
    LoRa模块：支持CN470频段，Class A/C模式，用于常规数据上报。

传感器接口：
    GPS模块：UART接口，周期获取经纬度、速度、航向。
    温度传感器：I2C/单总线接口，周期采集环境温度。
    风速传感器：脉冲/模拟量输入，通过MCU计算风速值。

电源管理：
    锂电池+太阳能充电（甲板部署节点）。
