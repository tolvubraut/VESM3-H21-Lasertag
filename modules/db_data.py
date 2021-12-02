from json.decoder import JSONDecodeError
from pathlib import Path
import json

class DbData:
    def __init__(self, data_file):
        # Gets data folder and appends the file to the path
        self.data_path = Path(__file__).resolve().parent.parent.joinpath(f'data/{data_file}')
    
    def write_data(self, data):
        with open(self.data_path, "r+") as f:
            try: 
                current_data = json.load(f)
                current_data.append(data)
                with open(self.data_path, "w") as f2:
                    json.dump(current_data, f2)
            except JSONDecodeError:
                json.dump([data], f)


    def get_data(self, line_quantity=None):
        with open(self.data_path, "r") as f:
            return json.load(f)
