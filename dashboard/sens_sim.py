import random
import numpy as np
import datetime

class fake_sim:
    def __init__(self):
        self.vol = self.close_norm_dist(450, 450, 10)
        self.fr = self.close_norm_dist(55, 55, 2)
        self.pres = self.close_norm_dist(12.50, 13, 0.5)
        self.last_update = datetime.datetime.now()

    def close_norm_dist(self, prev, mu, sd):
        retval = np.random.normal(mu, sd)

        for i in range(10):
            randvar = np.random.normal(mu, sd)
            if (abs(randvar-prev) < abs(retval-prev)):
                retval = randvar
        return retval

    def get_vol(self):
        self.update()
        return self.vol
    def get_fr(self):
        self.update()
        return self.fr
    def get_pres(self):
        self.update()
        return self.pres
    def update(self):
        if (datetime.datetime.now()-self.last_update) > datetime.timedelta(milliseconds=1000):
            self.last_update = datetime.datetime.now()
            self.vol = self.close_norm_dist(self.vol, 450, 10)
            self.fr = self.close_norm_dist(self.fr, 55, 2)
            self.pres = self.close_norm_dist(self.pres, 13, 0.5)
