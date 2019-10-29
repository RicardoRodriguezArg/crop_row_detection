import configparser


class ServerConfig():
    def __init__(self, ini_file):
        config = configparser.ConfigParser()
        config.read(ini_file)
        self.__config_dict = self.__create_config_dict(config)

    def __create_config_dict(self, config):
        result = dict()
        for section in config.sections():
            result[section] = self.__options_section_map(section, config)
        return result

    def __options_section_map(self, section, config):
        dict1 = {}
        options = config.options(section)
        for option in options:
            try:
                dict1[option] = config.get(section, option)
                if dict1[option] == -1:
                    print("skip: %s" % option)
            except:
                print("exception on %s!" % option)
                dict1[option] = None
        return dict1

    @property
    def configuration_dict(self):
        return self.__config_dict


class Utils:
    def __init__(self, config):
        section = config['ALLOWED_EXTENSIONS']
        self.allowed_extensions = section.split(',').strip().lower()

    def is_file_allowed(self, file):
        extension = file.split('.')[1]
        return extension in self.allowed_extensions
