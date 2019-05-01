class ScriptManager():
    def __init__(self):
        self.x_points = list()
        self.y_points = list()

    def read_clothoides_values(self, dict_options):
        filename = dict_options['script_filename']
        self.x_points = list()
        self.y_points = list()
        with open(filename, "r") as file:
            all_lines = file.readlines()
            for current_line in all_lines:
                if len(current_line) > 0:
                    x_point = (current_line.split(',')[0])
                    y_point = (current_line.split(',')[1])
                    self.x_points.append(float(x_point))
                    self.y_points.append(float(y_point))
        print ("#Points%d", len(self.x_points))
    
    def get_sampling_from_points(self, sampling_count=100):
        step = int(len(self.x_points) / sampling_count)
        
        x_sampled_points = list()
        y_sampled_points = list()
        for x_index in range(1,len(self.x_points), step):
            x_sampled_points.append(self.x_points[x_index])
            y_sampled_points.append(self.y_points[x_index])
            
                
        return x_sampled_points, y_sampled_points








