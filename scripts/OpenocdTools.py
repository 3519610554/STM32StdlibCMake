import json
import sys
import os
import subprocess

STLINK_TARGET="stm32f4x"
OPENOCD_PATH=fr"openocd.exe"

def create_folder(folder_path):
    if os.path.isdir(folder_path):
        return
    os.makedirs(folder_path)

def debug_json(target_name):
    debug_json_dict = {
        "cwd": "${workspaceRoot}",
        "type": "cortex-debug",
        "request": "launch",
        "name": f"{target_name}: Debug",
        "servertype": "openocd",
        "executable": "${workspaceFolder}/" + f"build/{target_name}.elf",
        "runToEntryPoint": "main",
        "configFiles": [
            "interface/stlink.cfg",
            f"target/{STLINK_TARGET}.cfg"
        ]
    }
    return debug_json_dict

def flash_json(target_name, flash_address):
    flash_json_dict = {   
        "name": f"{target_name}: Falsh",
        "type": "debugpy",
        "request": "launch",
        "program": "${workspaceFolder}/scripts/OpenocdTools.py",
        "args": ["flash", f"{target_name}", f"{flash_address}", "${workspaceFolder}"],
        "console": "integratedTerminal"
    }
    return flash_json_dict

def write_json(name, build_type, folder_path):

    configurations_json = []
    configurations_json.append(flash_json(name, "0x08000000"))
    if build_type == "Debug":
        configurations_json.append(debug_json(name))
    launch_json = {
        "version": "0.2.0",
        "configurations": configurations_json
    }

    with open(f'{folder_path}/launch.json', 'w') as json_file:
        print("write successfuly")
        json.dump(launch_json, json_file, indent=4)

def flash_FirmwareWithOpenocd(bin_file, flash_address="0x08000000"):
        download_path = bin_file.replace('\\', '/')
        command = [
            OPENOCD_PATH,
            "-f", "interface/stlink.cfg",       
            "-f", f"target/{STLINK_TARGET}.cfg",
            "-c", f"program {download_path} {flash_address} verify reset exit"
        ]
        subprocess.run(command)

if __name__ == '__main__':  
    command = sys.argv[1]
    print(f"command: {command}")
    if (command == "flash"):
        target_name = sys.argv[2]
        print(f"flash {target_name}")
        flash_address = sys.argv[3]
        flash_path = sys.argv[4] + fr"/build/{target_name}.bin"
        flash_FirmwareWithOpenocd(flash_path, flash_address)
    else:
        build_type = sys.argv[2]
        write_path = sys.argv[3] + "/.vscode"
        project_name = sys.argv[4]
        print(f"name: {project_name}")
        create_folder(write_path)
        print(f"path: {write_path}")
        write_json(project_name, build_type, write_path)
