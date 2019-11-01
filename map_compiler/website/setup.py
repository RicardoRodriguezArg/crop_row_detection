from distutils.core import setup

setup(
    name='MapCompilerWebSite',
    version='0.1dev',
    packages=['main_page',],
    packages=find_packages(),
    package_data={'main_page': ['data/*.ini', 'templates/*.html']},
    license='Creative Commons Attribution-Noncommercial-Share Alike license',
    install_requires=['Flask'],
    include_package_data=True,
    zip_safe=False,
    long_description=open('README.txt').read(),
)