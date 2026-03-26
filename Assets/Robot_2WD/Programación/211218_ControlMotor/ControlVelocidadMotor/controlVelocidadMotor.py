from pyRobotics import *
import time

############################### TIEMPOS DE MUESTREO #################################
tf = 60
ts = 0.1
t =  np.arange(0, tf+ts, ts)
N = len(t)

################################ CONDICIONES INICIALES #################################
hx = np.zeros(N+1)
hy = np.zeros(N+1)
phi = np.zeros(N+1)

hx[0] = 0
hy[0] = 0
phi[0] = 0 * np.pi/180

################################ VELOCIDAD DE REFERENCIA #################################
uRef = 0.1 * np.ones(N)
wRef = 0.2 * np.ones(N)

################################ BUCLE DE SIMULACIÓN #################################
for k in range(N):

    # integral numérica
    phi[k+1] = phi[k] + ts*wRef[k]

    # Modelo cinemático
    hxp = uRef[k] * np.cos(phi[k+1])
    hyp = uRef[k] * np.sin(phi[k+1])

    # integral numérica
    hx[k+1] = hx[k] + ts*hxp
    hy[k+1] = hy[k] + ts*hyp

############################### MODELO DE SIMULACIÓN #############################
pathStl = "stl"
color = ['green'] #, 'black','gray', 'gray', 'white', 'blue']
uniciclo = robotics(pathStl, color)

# dimensiones de la escena
xmin = -1
xmax = 1
ymin = -0.5
ymax = 1.5
zmin = 0
zmax = 1
bounds = [xmin, xmax, ymin, ymax, zmin, zmax]
uniciclo.configureScene(bounds)
uniciclo.initTrajectory(hx, hy)
escala =2

uniciclo.initRobot(hx, hy, phi, escala)
uniciclo.startSimulation(1, ts)



