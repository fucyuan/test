import os

def delete_executables():
    """删除当前目录中所有没有扩展名的可执行文件"""
    current_dir = os.getcwd()
    
    # 遍历当前目录中的所有文件
    for file in os.listdir(current_dir):
        # 检查文件是否为普通文件并且没有扩展名
        if os.path.isfile(file) and not os.path.splitext(file)[1]:
            try:
                os.remove(file)
                print(f"Deleted: {file}")
            except OSError as e:
                print(f"Error deleting {file}: {e.strerror}")

# 调用删除函数
delete_executables()
