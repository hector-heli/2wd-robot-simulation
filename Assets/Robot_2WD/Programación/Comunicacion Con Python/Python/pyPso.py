import sys
import numpy as np


class pso:
     def __init__(self,costFunction,swarmsize,npar):
          # Fase 1: Inicialización.
          #Paso 1.1: Asigne los parámetros para PSO, como swarm and particle size, coeficiente de aceleracion c1 y c2, gen = 0 y criterios de stop (como maxgen),etc.
          self.costFunction = costFunction
          self.summary = []
          self.c1  = 2.05 # parámetro cognitivo
          self.c2  = 4-self.c1 # parámetro social
          self.C   = 0.7298 #La aplicación de un factor de constricción en PSO es una estrategia útil para garantizar la convergencia del algoritmo de enjambre de partículas. 
          self.gen = 0    # generacion
          self.swarmsize = swarmsize
          self.npar = npar
          
          # Paso 1.2: Genera m ubicaciones iniciales y velocidades de las partículas. 
          self.x = np.random.rand(self.swarmsize,self.npar) 
          self.v = np.random.rand(self.swarmsize,self.npar) # velocidades aleatoria
    
          #Paso 1.3:  Calcule sus valores objetivos e inicialice las mejores ubicaciones locales y la mejor ubicación global.   
          self.cost=self.costFunction(self.x) # Evaluar población inicial usando funcion objetivo

          #Inicializar mínimo local para cada partícula
          self.localp = self.x.copy() # location of local minima
          self.localbest = self.cost.copy(); # cost of local minima

          #Encontrar la mejor partícula en la población inicial
          self.globalbest = self.cost.min()
          indx = np.where(self.cost == self.globalbest)
          self.globalp=self.x[indx[0][0],:]
          
     def run(self,maxgen=100):
          print("running PSO")
          while self.gen < maxgen:
               self.gen = self.gen + 1
               # Paso 2.1: Calcular parametros como peso de inercia r1, r2.
               w=(maxgen-self.gen)/maxgen # peso de inercia
               r1 = np.random.rand(self.swarmsize,self.npar) # numeros aleatorios
               r2 = np.random.rand(self.swarmsize,self.npar) # numeros aleatorios
               
               self.v = self.C*(w*self.v + self.c1*r1*(self.localp-self.x)+self.c2*r2*(np.ones((self.swarmsize,1))*self.globalp-self.x))
               # Paso 2.3: Actualizar las posiciones
               self.x = self.x + self.v
               underlimit = self.x  < 0.0001
               self.x = self.x*np.logical_not(underlimit)+underlimit*0.0001;

               self.cost=self.costFunction(self.x)
               # Paso 2.5: Actualización de la mejor posición local para cada partícula
               bestcost = self.cost < self.localbest
               self.localbest = self.localbest*np.logical_not(bestcost)+self.cost*bestcost
               self.localp[bestcost,:] = self.x[bestcost,:]
               #Paso 2.6: Actualización de la mejor posición global para cada partícula
               new_globalbest = self.localbest.min()
               if new_globalbest<self.globalbest:
                    indx = np.where(self.localbest == new_globalbest)
                    self.globalp=self.x[indx[0][0],:]
                    self.globalbest = new_globalbest
               self.summary.append(self.globalbest)     
                    
          print("finished PSO")          
               


          













