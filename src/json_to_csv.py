#!/usr/bin/env python
import pandas as pd
import json
from io import StringIO
import sys

if (len(sys.argv) != 2):
    print("Bad call to json_to_csv.py (converts the raw json from the database to csv format!)\n")
    exit()

output = StringIO()

# read json file
with open(sys.argv[1], 'r') as f:
    data = json.load(f)

# convert to dataframe
df = pd.json_normalize(data, record_path=['hits'])

# write to csv
df.to_csv(output, index=False)
print(output.getvalue())
