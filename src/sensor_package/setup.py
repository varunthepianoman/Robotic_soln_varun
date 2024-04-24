from setuptools import find_packages, setup

package_name = 'sensor_package'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='varun',
    maintainer_email='varunkamat23@gmail.com',
    description='Sensor server-client service for an automated sensor. Part of an application for a Robotics Software Engineer position at Machina Labs.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'my_node = sensor_package.my_node:main',
            'service = sensor_package.sensor_service:main',
            'client = sensor_package.sensor_client:main',

        ],
    },
)
