import json
import sys
import os
import logging
from config_init import openocd_init 

logging.basicConfig(level=logging.INFO,
                    format='[%(levelname)s] %(asctime)s - %(message)s')

STLINK_TARGET=""
OPENOCD_PATH=""

def create_folder(folder_path):
    if os.path.isdir(folder_path):
        return
    os.makedirs(folder_path)
    logging.info("创建 .vscode 成功")

def debug_json(target_name, bin_path):
    debug_json_dict = {
        "cwd": "${workspaceRoot}",
        "type": "cortex-debug",
        "request": "launch",
        "name": f"{target_name}: Debug",
        "servertype": "openocd",
        "executable": "${workspaceFolder}/" + f"{bin_path}/{target_name}.elf",
        "runToEntryPoint": "main",
        "configFiles": [
            "interface/stlink.cfg",
            f"target/{STLINK_TARGET}.cfg"
        ]
    }
    return debug_json_dict

def flash_json(target_name, flash_address, bin_path):
    flash_json_dict = {   
        "name": f"{target_name}: Falsh",
        "type": "debugpy",
        "request": "launch",
        "program": "${workspaceFolder}/scripts/util_opocd_download.py",
        "args": [flash_address, f"{bin_path}/{target_name}.bin"],
        "console": "integratedTerminal"
    }
    return flash_json_dict

def write_json(name, build_type, folder_path, bin_path):

    configurations_json = []
    configurations_json.append(flash_json(name, "0x08000000", bin_path))
    if build_type == "Debug":
        configurations_json.append(debug_json(name))
    launch_json = {
        "version": "0.2.0",
        "configurations": configurations_json
    }

    with open(f'{folder_path}/launch.json', 'w') as json_file:
        print("write successfuly")
        json.dump(launch_json, json_file, indent=4)

if __name__ == "__main__":

    build_type = sys.argv[1]
    write_path = sys.argv[2] + "/.vscode"
    bin_path = sys.argv[3]
    bin_name = sys.argv[4]

    STLINK_TARGET, OPENOCD_PATH = openocd_init()
    create_folder(write_path)
    write_json(bin_name, build_type, write_path, bin_path)
