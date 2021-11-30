from pathlib import Path

filepath = Path(__file__).resolve().parent.parent.joinpath('data/text.txt')
print(filepath)
with open(filepath, "w") as f:
    f.write("abcd")
