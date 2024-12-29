from alpha_vantage.timeseries import TimeSeries
import os
import pandas as pd

api_key = ''        # Add your API key here
ts = TimeSeries(key=api_key, output_format='pandas')

symbol = 'SPY'
data, meta_data = ts.get_daily(symbol=symbol, outputsize='full')

data.columns = ['open', 'high', 'low', 'close', 'volume']
data = data.iloc[::-1]

csv_path = 'prices/spy_daily.csv'


def get_missing_dates(existing_data, new_data):
    
    existing_dates = existing_data.index
    new_dates = new_data.index

    missing_dates = []
    for date in new_dates:
        if date not in existing_dates:
            missing_dates.append(date)
    return new_data.loc[missing_dates]


if os.path.exists(csv_path):
    
    existing_data = pd.read_csv(csv_path, index_col='date', parse_dates=True)
    last_date = existing_data.index.max()
    missing_data = get_missing_dates(existing_data, data)

    combined_data = pd.concat([existing_data, missing_data])
    combined_data = combined_data.sort_index()
    combined_data.to_csv(csv_path)
    print(f"Appended and ordered the data by date. Total rows: {len(combined_data)}")

else:
    data.to_csv(csv_path)
    print("Saved the data to a new CSV.")


print("Done webscraping")
