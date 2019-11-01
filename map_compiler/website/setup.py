from distutils.core import setup

setup(
    name='MapCompilerWebSite',
    version='0.1dev',
    packages=['main_page',],
    package_data={'main_page': ['data/*.ini']},
    license='Creative Commons Attribution-Noncommercial-Share Alike license',
    long_description=open('README.txt').read(),
)