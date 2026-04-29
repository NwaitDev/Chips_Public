import matplotlib.pyplot as plt

def read_csv_nowind(path):
    t = []; x = []; y = []; vx = []; vy = []; ux = []; uy = []
    with open(path, "r") as f:
        next(f)
        for line in f:
            v = line.strip().split(",")
            t.append(float(v[0]))
            x.append(float(v[1])); y.append(float(v[2]))
            vx.append(float(v[3])); vy.append(float(v[4]))
            ux.append(float(v[5])); uy.append(float(v[6]))
    return t, x, y, vx, vy, ux, uy

def read_csv_wind(path):
    t = []; x = []; y = []; vx = []; vy = []; ux = []; uy = []
    windAx = []; windAy = []
    with open(path, "r") as f:
        next(f)
        for line in f:
            v = line.strip().split(",")
            t.append(float(v[0]))
            x.append(float(v[1])); y.append(float(v[2]))
            vx.append(float(v[3])); vy.append(float(v[4]))
            ux.append(float(v[5])); uy.append(float(v[6]))
            windAx.append(float(v[7])); windAy.append(float(v[8]))
    return t, x, y, vx, vy, ux, uy, windAx, windAy

t0, x0, y0, vx0, vy0, ux0, uy0 = read_csv_nowind("lqr_drone_2d_nowind.csv")
t1, x1, y1, vx1, vy1, ux1, uy1, windAx, windAy = read_csv_wind("lqr_drone_2d_wind.csv")


plt.figure("Positions")
plt.plot(t0, x0, label="posX (no wind)")
plt.plot(t0, y0, label="posY (no wind)")
plt.plot(t1, x1, label="posX (wind)")
plt.plot(t1, y1, label="posY (wind)")
plt.xlabel("Time (s)")
plt.ylabel("Position (m)")
plt.title("Position Comparison")
plt.legend()
plt.grid(True)

plt.figure("Velocities")
plt.plot(t0, vx0, label="velX (no wind)")
plt.plot(t0, vy0, label="velY (no wind)")
plt.plot(t1, vx1, label="velX (wind)")
plt.plot(t1, vy1, label="velY (wind)")
plt.xlabel("Time (s)")
plt.ylabel("Velocity (m/s)")
plt.title("Velocity Comparison")
plt.legend()
plt.grid(True)

plt.figure("Control Inputs")
plt.plot(t0, ux0, label="ux (no wind)")
plt.plot(t0, uy0, label="uy (no wind)")
plt.plot(t1, ux1, label="ux (wind)")
plt.plot(t1, uy1, label="uy (wind)")
plt.xlabel("Time (s)")
plt.ylabel("Control (Force)")
plt.title("Control Inputs Comparison")
plt.legend()
plt.grid(True)

plt.show()
