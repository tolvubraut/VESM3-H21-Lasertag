from pathlib import Path

class DbData:
    def __init__(self, data_file):
        # Gets data folder and appends the file to the path
        self.data_path = Path(__file__).resolve().parent.parent.joinpath(f'data/{data_file}')
    
    def write_data(self, data):
        with open(self.data_path, "a") as f:
            f.writelines(f"{data}\n")

    def get_data(self):
        with open(self.data_path, "r") as f:
            return f.readlines()
