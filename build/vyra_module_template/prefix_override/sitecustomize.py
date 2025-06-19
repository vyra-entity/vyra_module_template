import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/holgder-dach/VYRA/vyra_module_template/install/vyra_module_template'
