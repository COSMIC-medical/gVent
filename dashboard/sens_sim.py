import random
import numpy as np
import datetime

class fake_sim:
    ins_vol_mu  = 0.450
    ex_vol_mu   = 0.450
    ins_vol_sd  = 0.01
    ex_vol_sd   = 0.01

    ins_fr_mu   = 55
    ex_fr_mu    = 55
    ins_fr_sd   = 2
    ex_fr_sd    = 2

    ins_pres_mu = 12.50
    ex_pres_mu  = 12.50
    ins_pres_sd = 0.5
    ex_pres_sd  = 0.5

    def __init__(self, port):
        self.ins_vol = self.close_norm_dist(self.ins_vol_mu, self.ins_vol_mu, self.ins_vol_sd)
        self.ex_vol = self.close_norm_dist(self.ex_vol_mu, self.ex_vol_mu, self.ex_vol_sd)

        self.ins_fr = self.close_norm_dist(self.ins_fr_mu, self.ins_fr_mu, self.ins_fr_sd)
        self.ex_fr = self.close_norm_dist(self.ex_fr_mu, self.ex_fr_mu, self.ex_fr_sd)

        self.ins_pres = self.close_norm_dist(self.ins_pres_mu, self.ins_pres_mu, self.ins_pres_sd)
        self.ex_pres = self.close_norm_dist(self.ex_pres_mu, self.ex_pres_mu, self.ex_pres_sd)
        self.last_update = datetime.datetime.now()

    def close_norm_dist(self, prev, mu, sd):
        retval = np.random.normal(mu, sd)
        for i in range(10):
            randvar = np.random.normal(mu, sd)
            if (abs(randvar-prev) < abs(retval-prev)):
                retval = randvar
        return retval

    def readline(self):
        self.update()
        return (str(self.ins_pres) + ', ' + str(self.ex_pres) + ', ' +
            str(self.ins_fr) + ', ' + str(self.ex_fr) + ', ' +
            str(self.ins_vol) + ', ' + str(self.ex_vol))

    def update(self):
        if (datetime.datetime.now()-self.last_update) > datetime.timedelta(milliseconds=100):
            self.ins_vol = self.close_norm_dist(self.ins_vol, self.ins_vol_mu, self.ins_vol_sd)
            self.ex_vol = self.close_norm_dist(self.ex_vol, self.ex_vol_mu, self.ex_vol_sd)

            self.ins_fr = self.close_norm_dist(self.ins_fr, self.ins_fr_mu, self.ins_fr_sd)
            self.ex_fr = self.close_norm_dist(self.ex_fr, self.ex_fr_mu, self.ex_fr_sd)

            self.ins_pres = self.close_norm_dist(self.ins_pres, self.ins_pres_mu, self.ins_pres_sd)
            self.ex_pres = self.close_norm_dist(self.ex_pres, self.ex_pres_mu, self.ex_pres_sd)
