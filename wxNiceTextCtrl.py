import wx
import HeeksCNC

class DoubleCtrl(wx.TextCtrl):
    def __init__(self, parent, id, factor = 1.0):
        wx.TextCtrl.__init__(self, parent, id)
        self.factor = factor
        
    def GetValue(self):
        return float(wx.TextCtrl.GetValue())/self.factor

    def DoubleToString(self, value):
        return str(value * self.factor)
    
    def SetValue(self, value):
        wx.TextCtrl.SetValue(self, self.DoubleToString(value))
        
class LengthCtrl(DoubleCtrl):
    def __init__(self, parent, id):
        #factor = 1.0/HeeksCNC.get_view_units()
        factor = 1.0
        DoubleCtrl.__init__(self, parent, id, factor)
        
class GeomCtrl(wx.TextCtrl):
    # for now this is just a list of profile names with quotes around them and spaces between them, but later it might have a diagram showing the geometry
    def __init__(self, parent, id):
        wx.TextCtrl.__init__(self, parent, id)
        
    def GetGeomList(self):
        str = wx.TextCtrl.GetValue()
        s = ""
        geom_list = []
        length = len(str)
        name_started = False
        for i in range(0, length):
            if str[i] == '"':
                if name_started:
                    geom_list.append[s]
                    s = ""
                    name_started = False
                else:
                    name_started = True
        return geom_list
    
    def SetFromGeomList(self, geom_list):
        first = True
        str = ""
        for geom in geom_list:
            if first == False:
                str = str + " "
            else:
                first = False
            str = str + '"' + geom + '"'
        wx.TextCtrl.SetValue(self, str)
        