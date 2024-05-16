import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv")

fig, ax = plt.subplots(2, 1)

df.plot(x="Time", y=["Value_0", "Value_1"], ax=ax[0])
df.plot(x="Value_0", y="Value_1", ax=ax[1], label='xy')
fig.savefig("plot.png")
