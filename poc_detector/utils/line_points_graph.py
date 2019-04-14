
class LinePointsGraph():
    def __init__(self):
        self.__vertex_list = dict()
        self.hash_map = dict()

    def add_point(self,frame_index, point_index):
        point = hash(frame_index * 10 + point_index)
        if not (point in self.__vertex_list):
            self.hash_map[point] = (frame_index, point_index)
            self.__vertex_list[point] = list()

    def get_point(self,frame_index, point_index):
        id = hash(frame_index *10 + point_index)
        return self.__vertex_list[id]

    def is_point_in_graph(self, frame_index, point_index):
        id = hash(frame_index * 10 + point_index)
        result = False
        if id in self.__vertex_list:
            result = True
        return result
    
    def add_edge(self, frame_index, point_index, next_frame_index, nex_point_index):
        current_id = hash(frame_index * 10 + point_index)
        if not (self.is_point_in_graph(frame_index, point_index)):
            self.add_point(frame_index, point_index)
        self.__add_neighboard(current_id, next_frame_index, nex_point_index)

    def __add_neighboard(self, current_id, next_frame_index, nex_point_index):
        next_point = hash(next_frame_index * 10 + nex_point_index)
        if not (next_point in self.hash_map):
            self.hash_map[next_point] = (next_frame_index, nex_point_index)
            self.__vertex_list[current_id].append(next_point)

    def show(self):
        print self.__vertex_list
        print "================="
        print self.hash_map

    def __compute_hash(self, first_value, second_value):
        return hash(first_value * 10 + second_value)

    def get_list_of_points(self, frame_index, point_index):
        list_points= list()
        current_key = self.__compute_hash(frame_index, point_index)
        is_done = False
        while (not is_done):
            if (current_key in self.__vertex_list):
                list_points.append(self.hash_map[current_key])
                next_key = self.__vertex_list[current_key]
                self.__vertex_list.pop(current_key)
                if len(next_key)==0:
                    is_done = True
                else:
                    current_key = next_key[0]
            else:
                is_done = True
        return list_points
            
                

