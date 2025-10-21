# entrypoint.sh - 根据 PTP_ROLE 环境变量启动对应 PTP 服务
#!/bin/bash 
set -e

# 读取环境变量
ROLE=${PTP_ROLE:-slave}
PRIORITY1=${PTP_PRIORITY1:-128}
PRIORITY2=${PTP_PRIORITY2:-128}
CLOCK_CLASS=${PTP_CLOCK_CLASS:-248}
CLOCK_ACCURACY=${PTP_CLOCK_ACCURACY:-255}
OFFSET_SCALED_LOG_VARIANCE=${PTP_OFFSET_SCALED_LOG_VARIANCE:-65535}
CONFIG_DIR="/etc/ptp"
LOG_FILE="/var/log/ptp.log"

echo "Starting PTP node with role: $ROLE" | tee -a $LOG_FILE
echo "Priority1: $PRIORITY1, Priority2: $PRIORITY2" | tee -a $LOG_FILE

# 替换配置文件中的占位符
for cfg_file in /etc/ptp/*.cfg; do
    sed -i "s/{{PRIORITY1}}/$PRIORITY1/g" "$cfg_file"
    sed -i "s/{{PRIORITY2}}/$PRIORITY2/g" "$cfg_file"
    sed -i "s/{{CLOCK_CLASS}}/$CLOCK_CLASS/g" "$cfg_file"
    sed -i "s/{{CLOCK_ACCURACY}}/$CLOCK_ACCURACY/g" "$cfg_file"
    sed -i "s/{{OFFSET_SCALED_LOG_VARIANCE}}/$OFFSET_SCALED_LOG_VARIANCE/g" "$cfg_file"
done

#python3 /scripts/ptp_mon.py &

# 根据角色启动对应脚本
case "$ROLE" in
    "master")
        echo "Configuring as PTP Master" | tee -a $LOG_FILE
        /scripts/start-master.sh "$CONFIG_DIR/master.cfg" &
        ;;
    "slave")
        echo "Configuring as PTP Slave" | tee -a $LOG_FILE
        /scripts/start-slave.sh "$CONFIG_DIR/slave.cfg" &
        ;;
    "bc")
        echo "Configuring as PTP Boundary Clock" | tee -a $LOG_FILE
        /scripts/start-bc.sh "$CONFIG_DIR/bc.cfg" &
        ;;
    "tc")
        echo "Configuring as PTP Transparent Clock" | tee -a $LOG_FILE
        /scripts/start-tc.sh "$CONFIG_DIR/tc.cfg" &
        ;;
    *)
        echo "Unknown role: $ROLE" | tee -a $LOG_FILE
        exit 1
        ;;
esac

# 持续运行，输出日志
tail -f $LOG_FILE