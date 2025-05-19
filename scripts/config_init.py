import os
import logging
import json

def openocd_init():
    file_path = os.path.dirname(os.path.abspath(__file__))
    config_file = os.path.join(file_path, "config.json")
    with open(config_file, 'r', encoding='utf-8') as f:
        data = json.load(f)
        STLINK_TARGET = data["openocd"]["target"]
        OPENOCD_PATH = data["openocd"]["path"]
        logging.info(f"stlink_target: {STLINK_TARGET}")
        logging.info(f"openocd_path: {OPENOCD_PATH}")
        return STLINK_TARGET, OPENOCD_PATH
    logging.error("获取初始化文件失败!")
    return "", ""
