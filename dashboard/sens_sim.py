import random
import numpy as np

class fake_sim:
    def __init__(self):
        self.prev_vol = 450.00
        self.prev_fr = 55.00
        self.prev_pres = 12.50

    def close_norm_dist(self, prev, mu, sd):
        retval = np.random.normal(mu, sd)

        for i in range(10):
            randvar = np.random.normal(mu, sd)
            if (abs(randvar-prev) < abs(retval-prev)):
                retval = randvar
        return retval

    def get_vol(self):
        self.prev_vol = self.close_norm_dist(self.prev_vol, 450, 10)
        return self.prev_vol
    def get_fr(self):
        self.prev_fr = self.close_norm_dist(self.prev_fr, 55, 2)
        return self.prev_fr
    def get_pres(self):
        self.prev_pres = self.close_norm_dist(self.prev_pres, 13, 0.5)
        return self.prev_pres
