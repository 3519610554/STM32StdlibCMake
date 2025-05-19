import os
import sys
import shutil
import logging

logging.basicConfig(level=logging.INFO,
                    format='[%(levelname)s] %(asctime)s - %(message)s')

def copy_file(src_file, dest_dir):
    
    if not os.path.isfile(src_file):
        return

    os.makedirs(dest_dir, exist_ok=True)

    dest_file = os.path.join(dest_dir, os.path.basename(src_file))

    try:
        shutil.copy2(src_file, dest_file)
        logging.info(f"文件已复制到: {dest_file}")
    except Exception as e:
        logging.error(f"复制失败: {e}")

if __name__ == "__main__":

    
    source = command = sys.argv[1]
    destination = command = sys.argv[2]

    logging.info(f"source: {source}")
    logging.info(f"destination: {destination}")

    copy_file(source, destination)
