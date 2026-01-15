import matplotlib.pyplot as plt

equity = []
with open("assets/equity_curve_txnc_enabled.csv") as f:
    for line in f:
        equity.append(float(line.strip()))

# with open("assets/equity_curve_txnc_disabled.csv") as f:
#     for line in f:
#         equity.append(float(line.strip()))


# SCALED TRANSACTION COST
# with open("assets/equity_curve_scaled_txnc_enabled.csv") as f:
#     for line in f:
#         equity.append(float(line.strip()))

plt.plot(equity)
plt.title("Equity Curve")
plt.xlabel("Trade Index")
plt.ylabel("Equity")
plt.savefig("assets/equity_curve_txnc_enabled.png")
print("equity_curve_txnc_enabled.png")
# plt.savefig("assets/equity_curve_txnc_disabled.png")
# print("equity_curve_txnc_disabled.png")


# SCALED TRANSACTION COST
# plt.savefig("assets/equity_curve_scaled_txnc_enabled.png")
# print("equity_curve_scaled_txnc_enabled.png")