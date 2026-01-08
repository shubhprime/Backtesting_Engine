import matplotlib.pyplot as plt

equity = []
with open("equity_curve.csv") as f:
    for line in f:
        equity.append(float(line.strip()))

plt.plot(equity)
plt.title("Equity Curve")
plt.xlabel("Trade Index")
plt.ylabel("Equity")
plt.savefig("equity_curve.png")
print("Saved equity_curve.png")