import numpy as np
import pandas as pd
import hall

# Proof of concept for the E vector live representation.
hall.init()
hall.init()


datarange = 16
data = np.zeros((datarange, 4), np.float32)
calibrate = np.zeros(4, np.float32)
avg = np.zeros(4, np.float32)

runavg = 64
calavg = 256

for i in range(calavg):
    hall.read(calibrate)
    calibrate = calibrate
    avg = avg + calibrate

calibrate = avg / calavg
        
for j in range(datarange):

    input("ready: <enter>")

    avg = np.zeros(4, np.float32)
    data_ = np.zeros(4, np.float32)
    
    for i in range(runavg):
        hall.read(data_)
        # print(data_)
        # data_ = data_ - calibrate
        avg = avg + data_
        
    
    avg = avg / runavg
    print(avg)

    data[j] = avg
    
pd.DataFrame(data).to_csv("../datadump/angular2.csv")
    
hall.end()
