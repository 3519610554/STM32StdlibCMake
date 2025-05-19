import json
import sys
import os
import subprocess
from config_init import openocd_init 

STLINK_TARGET=""
OPENOCD_PATH=""

def flash_FirmwareWithOpenocd(bin_file, flash_address="0x08000000"):
        download_path = bin_file.replace('\\', '/')
        command = [
            OPENOCD_PATH,
            "-f", "interface/stlink.cfg",       
            "-f", f"target/{STLINK_TARGET}.cfg",
            "-c", f"program {download_path} {flash_address} verify reset exit"
        ]
        subprocess.run(command)

if __name__ == "__main__":

    flash_address = sys.argv[1]
    flash_path = sys.argv[2]

    STLINK_TARGET, OPENOCD_PATH = openocd_init()
    flash_FirmwareWithOpenocd(flash_path, flash_address)
