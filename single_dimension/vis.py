import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv")

fig, ax = plt.subplots(1, 1)

df.plot(x="Time", y="Value", ax=ax)
fig.savefig("plot.png")
